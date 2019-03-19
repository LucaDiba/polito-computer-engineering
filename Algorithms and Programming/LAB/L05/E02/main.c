#include "header.h"

int main() {
    Item M[N][N];

    if(leggiFile(M, N, N) == -1)return -1;
    stampaItem(M, N, N);
    return 0;
}