#ifndef _ESERCIZI_H
#define _ESERCIZI_H

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include <string.h>

#define MAX_CHAR_ESERCIZI 50
//Esercizi
typedef struct{
    int id;
    char *nome, *categoria, *tipo;
} Esercizio;
typedef struct{
    int n;
    Esercizio *vettEsercizi;
} *TabEsercizi;


Esercizio EsercizioNULL();
int isEsercizioNULL(Esercizio esercizio);
//TabEsercizi inizializzaTabEsercizi();
TabEsercizi leggiEsercizi(char *nome_file);
void stampaEsercizio(Esercizio esercizio);
void stampaElencoEsercizi(TabEsercizi tabEsercizi);

Esercizio cercaEsercizio(char *nome_esericizio, TabEsercizi tab_esercizi);
Esercizio getEsercizioById(int id_esercizio, TabEsercizi tab_esercizi);

#endif //_ESERCIZI_H