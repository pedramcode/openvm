#ifndef OPENVM_VM_H
#define OPENVM_VM_H
#define MEM_SIZE (1 << 16)
#define STACK_SIZE 256

#include <stdint.h>
#include <openvm/registers.h>

/// @brief main structure that contains components of virtual machine
typedef struct {
    uint16_t memory[MEM_SIZE];
    uint16_t reg[_REG_COUNT];
    uint16_t origin;
} vm_t;

/// @brief creates a new virtual machine
/// @return pointer to instance of `vm_t`
vm_t *vm_create();

/// @brief free a virtual machine
/// @param vm pointer to `vm_t`
void vm_free(vm_t *vm);

/// @brief set value in specific register
/// @param vm pointer to `vm_t`
/// @param reg register index (enum starts with REG_*)
/// @param value value to set in register
void vm_register_set(vm_t *vm, uint8_t reg, uint16_t value);

/// @brief get value from specific register
/// @param vm pointer to `vm_t`
/// @param reg register index (enum starts with REG_*)
/// @return value inside register
uint16_t vm_register_get(vm_t *vm, uint8_t reg);

/// @brief set value in specific memory address
/// @param vm pointer to `vm_t`
/// @param address address of memory cell
/// @param value value to set inside the cell
void vm_memory_set(vm_t *vm, uint16_t address, uint16_t value);

/// @brief get value from memory cell
/// @param vm pointer to `vm_t`
/// @param address address of memory cell
/// @return value inside the cell
uint16_t vm_memory_get(vm_t *vm, uint16_t address);

/// @brief write bytecodes into vm memory
/// @param vm pointer to `vm_t`
/// @param origin origin address of source
/// @param source pointer to source bytecodes
/// @param length length of source
void vm_program_codebytes(vm_t *vm, uint16_t origin, uint16_t *source, uint16_t length);

/// @brief execute machine
/// @param vm pointer to `vm_t`
void vm_execute(vm_t *vm);

/// @brief push value into stack
/// @param vm pointer to `vm_t`
/// @param value value to get push
void vm_stack_push(vm_t *vm, uint16_t value);

/// @brief pop value from stack
/// @param vm pointer to `vm_t`
/// @return popped value
uint16_t vm_stack_pop(vm_t *vm);

/// @brief runs a software interupt
/// @param vm pointer to `vm_t`
/// @param int_code intrupt code
void vm_run_interupt(vm_t *vm, uint16_t int_code);

#endif