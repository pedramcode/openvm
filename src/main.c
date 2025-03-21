#include <vm/vm.h>

int main(int argc, char **argv) {
    uint16_t origin = 0;
    uint16_t bytecodes[] = {
        // MOV A #1998
        0b0000101000000000, 1998,
        // MOV B A
        0b0000100000100000,
        // ADD A #10
        0b0000001000000000, 10,
        // SUB B #10
        0b0000011000100000, 10,
        // STORE [0x1234] A
        0b0000110000000000,
        0b0001001000110100,
        // STORE [0x1235] B
        0b0000110001000000,
        0b0001001000110101,
        // STORE [0x1236] #1377
        0b0000111000000000,
        0b0001001000110111, 1377,
        // LOAD C [0x1236]
        0b0001000010000000,
        0b0001001000110111,
        // EXIT
        0b1111110000000000,
    };

    vm_t *vm = vm_new();
    vm_load_bytecodes(vm, origin, (sizeof(bytecodes) / sizeof(bytecodes[0])), bytecodes);
    vm_run(vm);
    vm_free(vm);
    return 0;
}