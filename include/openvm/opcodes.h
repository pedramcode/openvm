#ifndef OPENVM_OPCODE_H
#define OPENVM_OPCODE_H

enum {
    /// @brief MOVR [DEST_REG] [SRC_REG]
    OP_MOVR = 1,
    /// @brief MOVI [DEST_REG] #[IM]
    OP_MOVI,
    /// @brief ADDR [DEST_REG] [SRC_REG]
    OP_ADDR,
    /// @brief ADDI [DEST_REG] #[IM]
    OP_ADDI,
    /// @brief SUBR [DEST_REG] [SRC_REG]
    OP_SUBR,
    /// @brief SUBI [DEST_REG] #[IM]
    OP_SUBI,
    /// @brief CMPR [REG_A] [REG_B]
    OP_CMPR,
    /// @brief CMPI [REG] #[IM]
    OP_CMPI,
    /// @brief JMP #[OFFSET]
    OP_JMP,
    /// @brief JNZ #[OFFSET]
    OP_JNZ,
    /// @brief JZ #[OFFSET]
    OP_JZ,
    /// @brief JG #[OFFSET]
    OP_JG,
    /// @brief JL #[OFFSET]
    OP_JL,
    /// @brief JGE #[OFFSET]
    OP_JGE,
    /// @brief JLE #[OFFSET]
    OP_JLE,
    /// @brief PUSH [REG]
    OP_PUSH,
    /// @brief POP [REG]
    OP_POP,
    /// @brief STORER &[ADDR] [REG]
    OP_STORER,
    /// @brief STOREI &[ADDR] #[IM]
    OP_STOREI,
    /// @brief LOAD [DEST_REG] &[ADDR]
    OP_LOAD,
    /// @brief INT #[INT_CODE]
    OP_INT,
    /// @brief ANDR [DEST_REG] [SRC_REG]
    OP_ANDR,
    /// @brief ANDI [DEST_REG] #[IM]
    OP_ANDI,
    /// @brief ORR [DEST_REG] [SRC_REG]
    OP_ORR,
    /// @brief ORI [DEST_REG] #[IM]
    OP_ORI,
    /// @brief SHRR [DEST_REG] [SRC_REG]
    OP_SHRR,
    /// @brief SHRI [DEST_REG] #[IM]
    OP_SHRI,
    /// @brief SHLR [DEST_REG] [SRC_REG]
    OP_SHLR,
    /// @brief SHLI [DEST_REG] #[IM]
    OP_SHLI,
    /// @brief NOT [REG]
    OP_NOT,
    /// @brief END
    OP_END = 63,
};

enum {
    INT_IO = 0,
};

#endif