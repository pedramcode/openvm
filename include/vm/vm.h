#ifndef OPENVM_VM_VM_H
#define OPENVM_VM_VM_H
#define MEMORY_SIZE (1 << 16)

#include <stdint.h>
#include <stdbool.h>
#include <vm/registers.h>

typedef struct {
    uint16_t memory[MEMORY_SIZE];
    uint16_t reg[_REG_COUNT];
    uint16_t origin;
} vm_t;

vm_t *vm_new();
void vm_free(vm_t *vm);
void vm_load_bytecodes(vm_t *vm, uint16_t origin, uint16_t length, uint16_t* codes);
void vm_set_reg(vm_t *vm, uint16_t reg, uint16_t value);
uint16_t vm_get_reg(vm_t *vm, uint16_t reg);
void vm_store_mem(vm_t *vm, uint16_t address, uint16_t value);
uint16_t vm_load_mem(vm_t *vm, uint16_t address);
void vm_run(vm_t *vm);
void vm_set_flag(vm_t *vm, uint16_t flag, bool value);
bool vm_get_flag(vm_t *vm, uint16_t flag);

#endif