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
        // STORE [0x1236] #66
        0b0000111000000000,
        0b0001001000110111, 66,
        // LOAD C [0x1236]
        0b0001000010000000,
        0b0001001000110111,
        // DEC C
        0b0110010010000000,
        // INT 1 1
        0b0001100001000100,
        // MOV H 32
        0b0000101011100000, 25,
        // INC C
        0b0110000010000000,
        // INT 1 1
        0b0001100001000100,
        // DEC H
        0b0110010111000000,
        // CMP H 0
        0b0001011011100000, 0,
        // JNZ 21
        0b0010000000000000, 20,
        // MOV C 13
        0b0000101001000000, 13,
        // INT 1 1
        0b0001100001000100,
        // MOV C 10
        0b0000101001000000, 10,
        // INT 1 1
        0b0001100001000100,
        // MSTORE 14 #0x1000 "Hello World!\r\n"
        0b0110100000001110,
        0b0001000000000000, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 10, 13,
        // INT 0 0
        0b0001100000000000,
    };

    vm_t *vm = vm_new();
    vm_load_bytecodes(vm, origin, (sizeof(bytecodes) / sizeof(bytecodes[0])), bytecodes);
    vm_run(vm);
    vm_free(vm);
    return 0;
}