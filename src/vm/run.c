#include <vm/vm.h>
#include <vm/opcodes.h>
#include <exception.h>

#include <stdbool.h>

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
                vm_set_reg(vm, dest, r);

                vm_set_flag(vm, FLAG_ZRO, r == 0);
                vm_set_flag(vm, FLAG_CRY, r < op1);
                vm_set_flag(vm, FLAG_NEG, (r & 0x8000) != 0);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ op2) & 0x8000) == 0 && ((op1 ^ r) & 0x8000) != 0));
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
                vm_set_reg(vm, dest, r);

                vm_set_flag(vm, FLAG_ZRO, r == 0);
                vm_set_flag(vm, FLAG_CRY, op1 < op2);
                vm_set_flag(vm, FLAG_NEG, (r & 0x8000) != 0);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ op2) & 0x8000) != 0 && ((op1 ^ r) & 0x8000) != 0));
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
                vm_set_flag(vm, FLAG_NEG, (r & 0x8000) != 0);
                vm_set_flag(vm, FLAG_OVF, (((op1 ^ op2) & 0x8000) != 0 && ((op1 ^ r) & 0x8000) != 0));
                break;
            }
            case OP_INT:{
                break;
            }
            case OP_JMP:{
                break;
            }
            case OP_JNZ:{
                break;
            }
            case OP_JZ:{
                break;
            }
            case OP_JG:{
                break;
            }
            case OP_JL:{
                break;
            }
            case OP_JGE:{
                break;
            }
            case OP_JLE:{
                break;
            }
            case OP_SHR:{
                break;
            }
            case OP_SHL:{
                break;
            }
            case OP_AND:{
                break;
            }
            case OP_OR:{
                break;
            }
            case OP_NOT:{
                break;
            }
            case OP_XOR:{
                break;
            }
            case OP_PUSH:{
                break;
            }
            case OP_POP:{
                break;
            }
            case OP_CALL:{
                break;
            }
            case OP_RET:{
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
    }
}