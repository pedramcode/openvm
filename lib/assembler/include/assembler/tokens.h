#ifndef ASSEMBLER_TOKENS_H
#define ASSEMBLER_TOKENS_H

#include <stdint.h>

typedef enum {
    T_KW_MOV,
    T_KW_ADD,
    T_KW_SUB,
    T_KW_CMP,
    T_KW_JMP,
    T_KW_JNZ,
    T_KW_JZ,
    T_KW_JG,
    T_KW_JL,
    T_KW_JGE,
    T_KW_JLE,
    T_KW_PUSH,
    T_KW_POP,
    T_KW_STORE,
    T_KW_LOAD,
    T_KW_INT,
    T_KW_AND,
    T_KW_OR,
    T_KW_SHR,
    T_KW_SHL,
    T_KW_NOT,
    T_KW_INC,
    T_KW_DEC,
    T_KW_END,
    T_KW_REG_A,
    T_KW_REG_B,
    T_KW_REG_C,
    T_KW_REG_D,
    T_KW_REG_E,
    T_KW_REG_F,
    T_KW_REG_IP,
    T_KW_REG_SP,
    T_KW_REG_CR,
    T_KW_REG_SF,
    T_LITERAL,
    T_ADDRESS,
} type_t;

typedef enum {
    TYP_STR,
    TYP_NUM,
} val_t;

typedef struct {
    type_t type;

    val_t value_type;
    union {
        char *str_value;
        uint16_t num_value;
    };
} token_t;

token_t x = (token_t) {
    .value_type=TYP_NUM,
    .num_value=123,
};

#endif