#include <vm/vm.h>

#include <exception.h>

void vm_store_mem(vm_t *vm, uint16_t address, uint16_t value){
    if(address > MEMORY_SIZE) {
        raise("invalid memory access");
    }
    vm->memory[address] = value;
}

uint16_t vm_load_mem(vm_t *vm, uint16_t address){
    if(address > MEMORY_SIZE) {
        raise("invalid memory access");
    }
    return vm->memory[address];
}