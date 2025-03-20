#ifndef OPENVM_FILE_H
#define OPENVM_FILE_H

#include <stdint.h>

/// @brief read bytecode file to execute
/// @param path path of bytecode file
/// @param origin its an output value, origin of source codes to write in memory
/// @param length its an output value, length of instructions
/// @return array of 16bit instructions
uint16_t *read_bytecode_file(char* path, uint16_t *origin, uint16_t *length);

#endif