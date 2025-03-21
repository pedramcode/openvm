#include <exception.h>

#include <stdio.h>
#include <stdlib.h>

void raise(char *message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}