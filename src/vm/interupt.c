#include <vm/interupt.h>
#include <exception.h>
#include <stdio.h>
#include <stdlib.h>

void run_interupt(vm_t *vm, uint16_t module_id, uint16_t function_id){
    switch(module_id) {
        case 0: {
            // signal module
            break;
        }
        case 1: {
            // IO module
            switch(function_id) {
                case 0: {
                    // stdin
                    break;
                }
                case 1: {
                    // stdout
                    fprintf(stdout, "%c", vm_get_reg(vm, REG_C));
                    break;
                }
            }
            break;
        }
        default: {
            raise("invalid interupt module");
            break;
        }
    }
}