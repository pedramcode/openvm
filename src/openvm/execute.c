#include <openvm/vm.h>

#include <openvm/opcodes.h>
#include <openvm/exception.h>
#include <stdbool.h>
#include <stdio.h>

#define CURINS vm_memory_get(vm, vm_register_get(vm, REG_IP))

void _next(vm_t *vm) {
    vm_register_set(vm, REG_IP, vm_register_get(vm, REG_IP) + 1);
}

void vm_execute(vm_t *vm){
    bool running = true;

    while(running) {
        uint16_t instr = CURINS;
        uint16_t opcode = instr >> 10;

        switch(opcode) {
            case OP_END:{
                running = false;
                goto next;
                break;
            }
            case OP_MOVR:{
                uint16_t dest = (instr >> 6) & 0xf;
                uint16_t src = (instr >> 2) & 0xf;
                vm_register_set(vm, dest, vm_register_get(vm, src));
                goto next;
                break;
            }
            case OP_MOVI:{
                uint16_t dest = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                vm_register_set(vm, dest, src);
                goto next;
                break;
            }
            case OP_ADDR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t sum = vm_register_get(vm, r1) + vm_register_get(vm, r2);
                vm_register_set(vm, r1, sum);
                goto next;
                break;
            }
            case OP_ADDI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t sum = vm_register_get(vm, r1) + src;
                vm_register_set(vm, r1, sum);
                goto next;
                break;
            }
            case OP_SUBR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t sum = vm_register_get(vm, r1) - vm_register_get(vm, r2);
                vm_register_set(vm, r1, sum);
                goto next;
                break;
            }
            case OP_SUBI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t sum = vm_register_get(vm, r1) - src;
                vm_register_set(vm, r1, sum);
                goto next;
                break;
            }
            case OP_CMPR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t res = STAT_ZRO;
                if (vm_register_get(vm, r1) > vm_register_get(vm, r2)) {
                    res = STAT_POS;
                } else if (vm_register_get(vm, r1) < vm_register_get(vm, r2)) {
                    res = STAT_NEG;
                }
                vm_register_set(vm, REG_SF, res);
                goto next;
                break;
            }
            case OP_CMPI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t r2 = CURINS;
                uint16_t res = STAT_ZRO;
                if (vm_register_get(vm, r1) > vm_register_get(vm, r2)) {
                    res = STAT_POS;
                } else if (vm_register_get(vm, r1) < vm_register_get(vm, r2)) {
                    res = STAT_NEG;
                }
                vm_register_set(vm, REG_SF, res);
                goto next;
                break;
            }
            case OP_JMP: {
                uint16_t offset = (instr >> 6) & 0xf;
                vm_register_set(vm, REG_IP, vm->origin + offset);
                goto skip;
                break;
            }
            case OP_JNZ: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) != STAT_ZRO){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_JZ: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) == STAT_ZRO){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_JG: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) == STAT_POS){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_JL: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) == STAT_NEG){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_JGE: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) == STAT_POS || vm_register_get(vm, REG_SF) == STAT_ZRO){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_JLE: {
                uint16_t offset = (instr >> 6) & 0xf;
                if(vm_register_get(vm, REG_SF) == STAT_NEG || vm_register_get(vm, REG_SF) == STAT_ZRO){
                    vm_register_set(vm, REG_IP, vm->origin + offset);
                    goto skip;
                }
                goto next;
                break;
            }
            case OP_PUSH: {
                uint16_t reg = (instr >> 6) & 0xf;
                uint16_t val = vm_register_get(vm, reg);
                vm_stack_push(vm, val);
                goto next;
                break;
            }
            case OP_POP: {
                uint16_t reg = (instr >> 6) & 0xf;
                vm_register_set(vm, reg, vm_stack_pop(vm));
                goto next;
                break;
            }
            case OP_STORER: {
                uint16_t addr = (instr >> 6) & 0xf;
                uint16_t reg = (instr >> 2) & 0xf;
                vm_memory_set(vm, addr, vm_register_get(vm, reg));
                goto next;
                break;
            }
            case OP_STOREI: {
                uint16_t addr = (instr >> 6) & 0xf;
                uint16_t val = (instr >> 2) & 0xf;
                vm_memory_set(vm, addr, val);
                goto next;
                break;
            }
            case OP_LOAD: {
                uint16_t reg = (instr >> 6) & 0xf;
                uint16_t addr = (instr >> 2) & 0xf;
                vm_register_set(vm, reg, vm_memory_get(vm, addr));
                goto next;
                break;
            }
            case OP_INT: {
                uint16_t int_code = (instr >> 6) & 0xf;
                vm_run_interupt(vm, int_code);
                goto next;
                break;
            }
            case OP_ANDR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t res = vm_register_get(vm, r1) & vm_register_get(vm, r2);
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_ANDI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t res = vm_register_get(vm, r1) & src;
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_ORR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t res = vm_register_get(vm, r1) | vm_register_get(vm, r2);
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_ORI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t res = vm_register_get(vm, r1) | src;
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_SHRR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t res = vm_register_get(vm, r1) >> vm_register_get(vm, r2);
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_SHRI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t res = vm_register_get(vm, r1) >> src;
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_SHLR: {
                uint16_t r1 = (instr >> 6) & 0xf;
                uint16_t r2 = (instr >> 2) & 0xf;
                uint16_t res = vm_register_get(vm, r1) << vm_register_get(vm, r2);
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_SHLI: {
                uint16_t r1 = (instr >> 6) & 0xf;
                _next(vm);
                uint16_t src = CURINS;
                uint16_t res = vm_register_get(vm, r1) << src;
                vm_register_set(vm, r1, res);
                goto next;
                break;
            }
            case OP_NOT: {
                uint16_t reg = (instr >> 6) & 0xf;
                vm_register_set(vm, reg, ~vm_register_get(vm, reg));
                goto next;
                break;
            }
            case OP_INC: {
                uint16_t reg = (instr >> 6) & 0xf;
                vm_register_set(vm, reg, vm_register_get(vm, reg) + 1);
                goto next;
                break;
            }
            case OP_DEC: {
                uint16_t reg = (instr >> 6) & 0xf;
                vm_register_set(vm, reg, vm_register_get(vm, reg) - 1);
                goto next;
                break;
            }
            default: {
                raise("invalid opcode");
            }
        }

        next:
        _next(vm);
        skip:
    }
}