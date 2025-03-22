#include <vm/vm.h>
#include <exception.h>

void vm_set_flag(vm_t *vm, uint16_t flag, bool value){
    if(value) {
        uint16_t v = vm_get_reg(vm, REG_FR) | flag;
        vm_set_reg(vm, REG_FR, v);
    } else {
        uint16_t v = vm_get_reg(vm, REG_FR) & ~flag;
        vm_set_reg(vm, REG_FR, v);
    }
}

bool vm_get_flag(vm_t *vm, uint16_t flag){
    switch (flag){
        case (1 << 0): return (vm_get_reg(vm, REG_FR) >> 0) & 1;
        case (1 << 1): return (vm_get_reg(vm, REG_FR) >> 1) & 1;
        case (1 << 2): return (vm_get_reg(vm, REG_FR) >> 2) & 1;
        case (1 << 3): return (vm_get_reg(vm, REG_FR) >> 3) & 1;
        case (1 << 4): return (vm_get_reg(vm, REG_FR) >> 4) & 1;
        case (1 << 5): return (vm_get_reg(vm, REG_FR) >> 5) & 1;
        case (1 << 6): return (vm_get_reg(vm, REG_FR) >> 6) & 1;
        case (1 << 7): return (vm_get_reg(vm, REG_FR) >> 7) & 1;
        case (1 << 8): return (vm_get_reg(vm, REG_FR) >> 8) & 1;
        case (1 << 9): return (vm_get_reg(vm, REG_FR) >> 9) & 1;
        case (1 << 10): return (vm_get_reg(vm, REG_FR) >> 10) & 1;
        case (1 << 11): return (vm_get_reg(vm, REG_FR) >> 11) & 1;
        case (1 << 12): return (vm_get_reg(vm, REG_FR) >> 12) & 1;
        case (1 << 13): return (vm_get_reg(vm, REG_FR) >> 13) & 1;
        case (1 << 14): return (vm_get_reg(vm, REG_FR) >> 14) & 1;
        case (1 << 15): return (vm_get_reg(vm, REG_FR) >> 15) & 1;
        default:
            raise("invalid flag");
    }
    return false;
}