#include <vm/interupt.h>
#include <exception.h>
#include <stdio.h>
#include <stdlib.h>

void run_interupt(vm_t *vm, uint16_t module_id, uint16_t function_id){
    switch(module_id) {
        case 0: {
            // signal module
            switch(function_id) {
                case 0:
                    // EXIT 0
                    exit(0);
                    break;
                case 1:
                    // EXIT 1
                    exit(1);
                    break;
                default: {
                    raise("invalid signal function");
                    break;
                }
            }
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
                default: {
                    raise("invalid IO function");
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