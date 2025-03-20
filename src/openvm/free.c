#include <openvm/vm.h>
#include <stdlib.h>

void vm_free(vm_t *vm){
    free(vm);
}