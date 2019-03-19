#include "header.h"

int main(int argc, char **argv) {
    char **set = NULL;
    int nr;

    if((nr=leggiFile(argv[1], &set))==-1)return -1;
    stringGenerator(nr, &set);

    return 0;
}