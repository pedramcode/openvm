#include <vm/vm.h>

#include <malloc.h>

vm_t *vm_new(){
    vm_t *vm = malloc(sizeof(vm_t));
    vm_set_reg(vm, REG_FR, 0);
    vm_set_reg(vm, REG_SP, 0);
    return vm;
}

void vm_free(vm_t *vm){
    free(vm);
}