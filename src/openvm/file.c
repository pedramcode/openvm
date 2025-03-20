#include <openvm/file.h>

#include <openvm/exception.h>
#include <stdio.h>
#include <malloc.h>

uint16_t *read_bytecode_file(char* path, uint16_t *origin, uint16_t *length){
    FILE *file = fopen(path, "rb");
    uint16_t instr;

    if(!fread(&instr, sizeof(uint16_t), 1, file)){
        raise("bad bytecode format");
    }
    if(instr != 0x1998){
        raise("bad bytecode format");
    }

    if(!fread(&instr, sizeof(uint16_t), 1, file)){
        raise("bad bytecode format");
    }
    uint16_t len = instr;
    (*length) = len;

    if(!fread(&instr, sizeof(uint16_t), 1, file)){
        raise("bad bytecode format");
    }
    (*origin) = instr;

    uint16_t *data = malloc(sizeof(uint16_t) * len);

    uint16_t i = 0;
    while(fread(&instr, sizeof(uint16_t), 1, file)){
        data[i++] = instr;
    }

    fclose(file);
    return data;
}