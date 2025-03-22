#include <vm/vm.h>

void vm_load_bytecodes(vm_t *vm, uint16_t origin, uint16_t length, uint16_t* codes){
    vm_set_reg(vm, REG_PC, origin);
    vm->origin = origin;
    for(uint16_t i = 0 ; i < length ; i++){
        vm_store_mem(vm, origin + i, codes[i]);
    }
}