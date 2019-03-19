#ifndef E03_ATLETA_H
#define E03_ATLETA_H

#define MAX_ELEMENTI 8

typedef struct {
    int maxNA, maxAA, maxAI, maxSUM, best_soluzione[MAX_ELEMENTI];
    float best_punteggio;
}* Atleta;

Atleta LeggiAtleta(char **x);

#endif //E03_ATLETA_H