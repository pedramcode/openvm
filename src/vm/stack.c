#include <vm/vm.h>
#include <exception.h>

void vm_stack_push(vm_t *vm, uint16_t value){
    if(vm_get_reg(vm, REG_SP) >= STACK_SIZE) {
        raise("stack overflow");
    }
    vm_store_mem(vm, MEMORY_SIZE - 1 - vm_get_reg(vm, REG_SP), value);
    vm_set_reg(vm, REG_SP, vm_get_reg(vm, REG_SP) + 1);
}

uint16_t vm_stack_pop(vm_t *vm){
    if(vm_get_reg(vm, REG_SP) == 0){
        raise("stack underflow");
    }
    uint16_t val = vm_load_mem(vm, MEMORY_SIZE - 1 - vm_get_reg(vm, REG_SP) - 1);
    vm_set_reg(vm, REG_SP, vm_get_reg(vm, REG_SP) - 1);
    return val;
}