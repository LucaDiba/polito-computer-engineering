#ifndef E02_ESERCIZI_H
#define E02_ESERCIZI_H

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include <string.h>

#define MAX_CHAR_ESERCIZI 50
//Esercizi
typedef struct{
    char *nome;
    char *categoria, *tipo;
} Esercizio;
typedef Esercizio* p_Esercizio;
typedef struct{
    int n;
    Esercizio *vettEsercizi;
} *TabEsercizi;
/*
typedef struct piano{
    Esercizio *esercizio;
    int set, rip;
} Piano;
typedef struct nodo_piano{
    Piano val;
    link_piano next;
} NodoPiano;
*/
/*
void stampaEsercizi(TabEsercizi);
Esercizio* getEsercizioPointerFromName(char *, TabEsercizi);
void leggiPiani(TabAtleti, TabEsercizi);
void stampaPiano(TabAtleti, char *);
int stampaPianoSuFile(FILE *fp, Atleta *atleta);
void modificaEsercizioPiano(Piano *);*/

TabEsercizi leggiEsercizi(char *nome_file);
p_Esercizio cercaEsercizioPerNome(char *nome_esercizio, TabEsercizi tab_esercizi);
stampaEsercizio(p_Esercizio esercizio);

#endif //E02_ESERCIZI_H