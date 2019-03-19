#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include "categoria.h"

Categorie leggiFile(FILE *fp) {
    int i;
    char nome[N];
    Categorie x = malloc(sizeof(*x));

    fscanf(fp, "%d %d %d", &x->numAA, &x->numAI, &x->numNA);
    x->numTOT = x->numAA + x->numAI + x->numNA;
    x->elementi = malloc(x->numTOT * sizeof(*(x->elementi)));

    for (i = 0; i < x->numTOT; i++) {
        fscanf(fp, "%s %d %f", nome, &x->elementi[i].grado, &x->elementi[i].punti);
        x->elementi[i].nome = strdup(nome);
    }

    return x;
}

TipoCategoria getTipoCategoria(int n, Categorie categorie){
    if(n < categorie->numNA)
        return cat_non_acrobatico;

    if(n >= categorie->numNA && n < (categorie->numNA + categorie->numAA))
        return cat_acrobatico_avanti;

    if(n >= (categorie->numNA + categorie->numAA) && n < (categorie->numNA + categorie->numAA + categorie->numAI))
        return cat_acrobatico_indietro;

    printf("Errore recupero tipo categoria");
    exit(EXIT_FAILURE);
}