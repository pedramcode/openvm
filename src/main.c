#include <openvm/vm.h>
#include <openvm/file.h>
#include <openvm/exception.h>

#include <assembler/echo.h>

int main(int argc, char **argv) {
    echo("hello world!");
    vm_t *vm = vm_create();

    if(argc != 2) {
        raise("bytecode file not provided");
    }
    uint16_t origin;
    uint16_t length;
    uint16_t *source = read_bytecode_file(argv[1], &origin, &length);
    vm_program_codebytes(vm, origin, source, length);
    vm_execute(vm);

    vm_free(vm);
    return 0;
}