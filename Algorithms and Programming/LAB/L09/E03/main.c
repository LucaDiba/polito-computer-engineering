#include <stdio.h>
#include <stdlib.h>
#include "atleta.h"
#include "categoria.h"

int esigenzaDiComposizione(int *sol, Categorie);
int esigenzaDiUscita(int *sol, Categorie);
void conteggioPunti(int *sol, Categorie, Atleta);
void disp_rip(int pos, int *val, int *sol, int, Atleta, Categorie);
void generaRoutine(Atleta, Categorie);

int main(int argv, char **argc) {
    Categorie categorie;
    Atleta atleta = LeggiAtleta(argc);
    int i;
    FILE *fp=NULL;

    if((fp=fopen("elementi.txt", "r")) == NULL){
        printf("Errore nell'apertura del file 1");
        return EXIT_FAILURE;
    }
    categorie = leggiFile(fp);
    fclose(fp);

    generaRoutine(atleta, categorie);

    if((fp=fopen("vincitore.txt", "w")) == NULL){
        printf("Errore nell'apertura del file 2");
        return EXIT_FAILURE;
    }

    fprintf(fp,"Punteggio massimo: %.2f\n",atleta->best_punteggio);
    for (i = 0; i < MAX_ELEMENTI; i++) {
        fprintf(fp, "%s\n", categorie->elementi[atleta->best_soluzione[i]].nome);
    }

    fclose(fp);

    return 0;
}

void generaRoutine(Atleta atleta, Categorie categorie) {
    int sol[MAX_ELEMENTI], i;
    int *val = malloc(categorie->numTOT * sizeof(int));

    for (i = 0; i < categorie->numTOT; i++)
        val[i] = i;

    printf("Richiamo disp_rip");
    disp_rip(0, val, sol, 0, atleta, categorie);

}

void disp_rip(int pos, int *val, int *sol, int difficolta_complessiva, Atleta atleta, Categorie categorie) {
    int i;
    if(pos>0){ // Pruning
        // Controllo se ultimo elemento aggiunto e` eseguibile dall'atleta
        if(getTipoCategoria(sol[pos-1], categorie) == cat_non_acrobatico      && atleta->maxNA < categorie->elementi[sol[pos-1]].grado)
            return;
        if(getTipoCategoria(sol[pos-1], categorie) == cat_acrobatico_avanti   && atleta->maxAA < categorie->elementi[sol[pos-1]].grado)
            return;
        if(getTipoCategoria(sol[pos-1], categorie) == cat_acrobatico_indietro && atleta->maxAI < categorie->elementi[sol[pos-1]].grado)
            return;

        // Controllo se somma elementi e` eseguibile dall'atleta
        if(difficolta_complessiva > atleta->maxSUM)
            return;
    }
    if (pos >= MAX_ELEMENTI) { // Terminazione: ogni atleta deve presentare esattamente 8 elementi
        conteggioPunti(sol, categorie, atleta);
        return;
    }
    printf("Pos: %d\n", pos);
    for (i = 0; i < categorie->numTOT; i++) {
        sol[pos] = val[i];
        disp_rip(pos + 1, val, sol, difficolta_complessiva + categorie->elementi[sol[pos]].grado, atleta, categorie);
    }
}

void conteggioPunti(int *sol, Categorie categorie, Atleta atleta) {
    float punteggio = 0;
    int tmp[MAX_ELEMENTI], i, j;

    for (i = 0; i < MAX_ELEMENTI; i++)
        tmp[i] = sol[i];

    //elimina doppi
    for(i = 0; i < MAX_ELEMENTI-1; i++) {
        for(j = i+1; j < MAX_ELEMENTI; j++) {
            if(tmp[i] == tmp[j])
                tmp[j] = -1;
        }
    }

    if (esigenzaDiComposizione(sol, categorie) || esigenzaDiUscita(sol, categorie)) {
        punteggio += 2.5;
    }

    for(i = 0; i < MAX_ELEMENTI; i++) {
        if(tmp[i] != -1)
            punteggio += categorie->elementi[sol[i]].punti;
    }

    if (punteggio > atleta->best_punteggio) {
        atleta->best_punteggio = punteggio;
        for (i = 0; i < MAX_ELEMENTI; i++) {
            atleta->best_soluzione[i] = sol[i];
        }
    }
}

int esigenzaDiComposizione(int *sol, Categorie categorie) {
    int i, eseguito[3] = {0}; //eseguito[0]: non_acr, eseguito[1]: acr_avanti, eseguito[2]: acr_indietro

    for (i = 0; i < MAX_ELEMENTI; i++) {
        if(eseguito[0] == 0 && getTipoCategoria(sol[i], categorie) == cat_non_acrobatico)
            eseguito[0] = 1;
        else if(eseguito[1] == 0 && getTipoCategoria(sol[i], categorie) == cat_acrobatico_avanti)
            eseguito[1] = 1;
        else if(eseguito[2] == 0 && getTipoCategoria(sol[i], categorie) == cat_acrobatico_indietro)
            eseguito[2] = 1;

        if(eseguito[0] + eseguito[1] + eseguito[2] > 1)
            return 1;
    }

    return 0;
}

int esigenzaDiUscita(int *sol, Categorie categorie){
    int ultimo_elemento = MAX_ELEMENTI-1;
    if(sol[ultimo_elemento] >= categorie->numNA //programma terminato con elemento acrobatico (avanti o indietro)
       && categorie->elementi[sol[ultimo_elemento]].grado >= 5) { //di grado almeno 5
        return 1;
    }else{
        return 0;
    }
}