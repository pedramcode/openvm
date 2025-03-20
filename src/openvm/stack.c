#include <openvm/vm.h>

#include <openvm/exception.h>

void vm_stack_push(vm_t *vm, uint16_t value) {
    if(vm_register_get(vm, REG_SP) >= STACK_SIZE) {
        raise("stack overflow");
    }
    vm_memory_set(vm, (MEM_SIZE - 1) - vm_register_get(vm, REG_SP), value);
    vm_register_set(vm, REG_SP, vm_register_get(vm, REG_SP) + 1);
}

uint16_t vm_stack_pop(vm_t *vm){
    if(vm_register_get(vm, REG_SP) == 0){
        raise("pop from empty stack");
    }
    uint16_t res = vm_memory_get(vm, (MEM_SIZE - 1) - vm_register_get(vm, REG_SP) - 1);
    vm_register_set(vm, REG_SP, vm_register_get(vm, REG_SP) - 1);
    return res;
}