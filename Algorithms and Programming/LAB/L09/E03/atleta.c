#include <malloc.h>
#include "atleta.h"

Atleta LeggiAtleta(char **argc) {
    Atleta atleta = malloc(sizeof(*atleta));
    atleta->maxNA = atoi(argc[1]);
    atleta->maxAA = atoi(argc[2]);
    atleta->maxAI = atoi(argc[3]);
    atleta->maxSUM = atoi(argc[4]);
    atleta->best_punteggio = -1;
    return atleta;
}