#include <vm/vm.h>

#include <exception.h>

void vm_set_reg(vm_t *vm, uint16_t reg, uint16_t value){
    if(reg >= _REG_COUNT){
        raise("invalid register");
    }
    vm->reg[reg] = value;
}

uint16_t vm_get_reg(vm_t *vm, uint16_t reg){
    if(reg >= _REG_COUNT){
        raise("invalid register");
    }
    return vm->reg[reg];
}