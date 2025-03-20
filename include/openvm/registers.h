#ifndef OPENVM_REGISTERS_H
#define OPENVM_REGISTERS_H

#include <stdint.h>

enum {
    REG_A = 0,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_F,
    REG_IP, // instruction pointer
    REG_SP, // stack pointer
    REG_CR, // carry
    REG_SF, // state flag
    _REG_COUNT,
};

enum {
    STAT_ZRO = 0,
    STAT_POS,
    STAT_NEG,
};

#endif