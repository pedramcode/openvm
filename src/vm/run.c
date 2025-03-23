#include <vm/vm.h>
#include <vm/opcodes.h>
#include <exception.h>
#include <vm/interupt.h>
#include <stdbool.h>
#include <stdio.h>

uint16_t _get_current_bytecode(vm_t *vm) {
    return vm_load_mem(vm, vm_get_reg(vm, REG_PC));
}

void _inc_pc(vm_t *vm) {
    vm_set_reg(vm, REG_PC, vm_get_reg(vm, REG_PC) + 1);
}

void vm_run(vm_t *vm){
    bool running = true;
    while(running){
        uint16_t bytecode = _get_current_bytecode(vm);
        uint16_t opcode = bytecode >> 10;
        switch(opcode){
            case OP_ADD:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 + op2;

                vm_set_flag(vm, FLAG_ZRO, r == 0);
                vm_set_flag(vm, FLAG_CRY, r < op1);
                vm_set_flag(vm, FLAG_NEG, r & 0x8000);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ r) & (op2 ^ r)) & 0x8000) != 0);

                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_SUB:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 - op2;

                vm_set_flag(vm, FLAG_ZRO, r == 0);
                vm_set_flag(vm, FLAG_CRY, op1 < op2);
                vm_set_flag(vm, FLAG_NEG, r & 0x8000);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ op2) & 0x8000) && ((op1 ^ r) & 0x8000)));

                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_MOV:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;
                if(mode == MOD_REG) {
                    vm_set_reg(vm, dest, vm_get_reg(vm, src));
                } else {
                    _inc_pc(vm);
                    vm_set_reg(vm, dest, _get_current_bytecode(vm));
                }
                break;
            }
            case OP_STORE:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t src = (bytecode >> 5) & 0xf;
                _inc_pc(vm);
                uint16_t addr = _get_current_bytecode(vm);
                if(mode == MOD_REG) {
                    vm_store_mem(vm, addr, vm_get_reg(vm, src));
                } else {
                    _inc_pc(vm);
                    vm_store_mem(vm, addr, _get_current_bytecode(vm));
                }
                break;
            }
            case OP_LOAD:{
                uint16_t dest = (bytecode >> 6) & 0xf;
                _inc_pc(vm);
                uint16_t addr = _get_current_bytecode(vm);
                vm_set_reg(vm, dest, vm_load_mem(vm, addr));
                break;
            }
            case OP_CMP:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 - op2;

                vm_set_flag(vm, FLAG_ZRO, r == 0);
                vm_set_flag(vm, FLAG_CRY, op1 < op2);
                vm_set_flag(vm, FLAG_NEG, r & 0x8000);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ op2) & 0x8000) && ((op1 ^ r) & 0x8000)));

                break;
            }
            case OP_INT:{
                uint16_t module = (bytecode >> 6) & 0xf;
                uint16_t function_id = (bytecode >> 2) & 0xf;
                run_interupt(vm, module, function_id);
                break;
            }
            case OP_JMP:{
                _inc_pc(vm);
                uint16_t offset = _get_current_bytecode(vm);
                vm_set_reg(vm, REG_PC, vm->origin + offset);
                goto skip;
                break;
            }
            case OP_JNZ:{
                if(!vm_get_flag(vm, FLAG_ZRO)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_JZ:{
                if(vm_get_flag(vm, FLAG_ZRO)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_JG:{
                if(!vm_get_flag(vm, FLAG_ZRO) && !vm_get_flag(vm, FLAG_CRY)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_JL:{
                if(!vm_get_flag(vm, FLAG_ZRO) && vm_get_flag(vm, FLAG_CRY)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_JGE:{
                if(vm_get_flag(vm, FLAG_ZRO) || !vm_get_flag(vm, FLAG_CRY)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_JLE:{
                if(vm_get_flag(vm, FLAG_ZRO) || vm_get_flag(vm, FLAG_CRY)){
                    _inc_pc(vm);
                    uint16_t offset = _get_current_bytecode(vm);
                    vm_set_reg(vm, REG_PC, vm->origin + offset);
                    goto skip;
                }
                break;
            }
            case OP_SHR:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 >> op2;
                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_SHL:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 << op2;
                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_AND:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 & op2;
                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_OR:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 | op2;
                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_NOT:{
                uint16_t dest = (bytecode >> 6) & 0xf;
                vm_set_reg(vm, dest, ~vm_get_reg(vm, dest));
                break;
            }
            case OP_XOR:{
                uint8_t mode = (bytecode >> 9) & 1;
                uint16_t dest = (bytecode >> 5) & 0xf;
                uint16_t src = (bytecode >> 1) & 0xf;

                uint16_t op1 = vm_get_reg(vm, dest);
                uint16_t op2 = 0;
                uint16_t r = 0;

                if(mode == MOD_REG) {
                    op2 = vm_get_reg(vm, src);
                } else {
                    _inc_pc(vm);
                    op2 = _get_current_bytecode(vm);
                }
                r = op1 ^ op2;
                vm_set_reg(vm, dest, r);
                break;
            }
            case OP_PUSH:{
                uint8_t register_to_push = (bytecode >> 6) & 1;
                vm_stack_push(vm, vm_get_reg(vm, register_to_push));
                break;
            }
            case OP_POP:{
                uint8_t register_to_pop = (bytecode >> 6) & 1;
                vm_set_reg(vm, register_to_pop, vm_stack_pop(vm));
                break;
            }
            case OP_CALL:{
                vm_stack_push(vm, vm_get_reg(vm, REG_PC));
                _inc_pc(vm);
                uint16_t offset = _get_current_bytecode(vm);
                vm_set_reg(vm, REG_PC, vm->origin + offset);
                goto skip;
                break;
            }
            case OP_RET:{
                vm_set_reg(vm, REG_PC, vm_stack_pop(vm) + 1);
                goto skip;
                break;
            }
            case OP_INC:{
                uint16_t dest = (bytecode >> 6) & 0xf;
                vm_set_reg(vm, dest, vm_get_reg(vm, dest) + 1);
                break;
            }
            case OP_DEC:{
                uint16_t dest = (bytecode >> 6) & 0xf;
                vm_set_reg(vm, dest, vm_get_reg(vm, dest) - 1);
                break;
            }
            case OP_END:{
                running = false;
                break;
            }
            default: {
                raise("invalid opcode");
                break;
            }
        }

        _inc_pc(vm);
        skip:
    }
}