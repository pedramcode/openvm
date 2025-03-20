#include <openvm/vm.h>
#include <malloc.h>

vm_t *vm_create(){
    vm_t *vm = calloc(1, sizeof(vm_t));
    vm_register_set(vm, REG_SF, STAT_ZRO);
    vm_register_set(vm, REG_IP, 0);
    vm_register_set(vm, REG_SP, 0);
    vm_register_set(vm, REG_CR, 0);
    return vm;
}