#ifndef OPENVM_VM_OPCODES_H
#define OPENVM_VM_OPCODES_H

enum {
    MOD_REG = 0,
    MOD_IMM,
};

enum {
    OP_ADD = 0,
    OP_SUB,
    OP_MOV,
    OP_STORE,
    OP_LOAD,
    OP_CMP,
    OP_INT,
    OP_JMP,
    OP_JNZ,
    OP_JZ,
    OP_JG,
    OP_JL,
    OP_JGE,
    OP_JLE,
    OP_SHR,
    OP_SHL,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_XOR,
    OP_PUSH,
    OP_POP,
    OP_CALL,
    OP_RET,
    OP_INC,
    OP_DEC,
    OP_MSTORE,
};

enum {
    FLAG_ZRO = 1, // if result is 0
    FLAG_NEG = 2, // if result is negative
    FLAG_CRY = 4, // if unsigned overflow occured (carry)
    FLAG_OVF = 8, // if signed overflow occured
};

#endif
