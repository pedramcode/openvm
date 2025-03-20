#include <openvm/vm.h>

#include <stdlib.h>
#include <stdio.h>

void vm_program_codebytes(vm_t *vm, uint16_t origin, uint16_t *source, uint16_t length){
    vm_register_set(vm, REG_IP, origin);
    vm->origin = origin;
    for(uint16_t i = 0 ; i < length ; i++){
        vm_memory_set(vm, origin + i, source[i]);
    }
    free(source);
}