#ifndef E03_CATEGORIA_H
#define E03_CATEGORIA_H

#include "elemento.h"

#define N 50

typedef struct {
    int numNA, numAA, numAI, numTOT;
    Elementi elementi;
}* Categorie;
typedef enum {
    cat_non_acrobatico, cat_acrobatico_avanti, cat_acrobatico_indietro
} TipoCategoria;

Categorie leggiFile(FILE*);
TipoCategoria getTipoCategoria(int n, Categorie);

#endif //E03_CATEGORIA_H
