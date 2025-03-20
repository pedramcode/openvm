#include <openvm/exception.h>

void raise(char *message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}