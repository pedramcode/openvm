#include <openvm/vm.h>

#include <openvm/opcodes.h>
#include <openvm/exception.h>

void _int_run_io(vm_t *vm) {
    uint16_t params = vm_register_get(vm, REG_A);
    uint16_t func_id = (params >> 11);

    switch(func_id){
        // stdout print
        case 0x0001:{
            unsigned char character = (params >> 3) & 0xff;
            fprintf(stdout, "%c", character);
            break;
        }
        default: {
            raise("invalid IO function id");
        }
    }
}

void vm_run_interupt(vm_t *vm, uint16_t int_code){
    switch(int_code){
        case INT_IO: {
            _int_run_io(vm);
            break;
        }
        default: {
            raise("invalid interupt code");
            break;
        }
    }
}