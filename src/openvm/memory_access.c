#include <openvm/vm.h>
#include <openvm/exception.h>

void vm_memory_set(vm_t *vm, uint16_t address, uint16_t value){
    if(address >= MEM_SIZE) {
        raise("invalid memory access");
    }
    vm->memory[address] = value;
}

uint16_t vm_memory_get(vm_t *vm, uint16_t address){
    if(address >= MEM_SIZE) {
        raise("invalid memory access");
    }
    return vm->memory[address];
}