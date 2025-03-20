#include <openvm/vm.h>
#include <openvm/exception.h>

void vm_register_set(vm_t *vm, uint8_t reg, uint16_t value){
    if(reg >= _REG_COUNT) {
        raise("invalid register access");
    }
    vm->reg[reg] = value;
}

uint16_t vm_register_get(vm_t *vm, uint8_t reg){
    if(reg >= _REG_COUNT) {
        raise("invalid register access");
    }
    return vm->reg[reg];
}