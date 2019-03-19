#ifndef _ATLETA_H
#define _ATLETA_H

#include <stdio.h>

typedef struct s_Atleta* Atleta;
typedef enum {
    byCodice, byCognome
} Metodo;

/* NULL */
Atleta AtletaNULL();
int isAtletaNULL(Atleta atleta);
Atleta newAtletaMonteOre(Atleta atleta, int nuovo_monteore);
Atleta newAtleta(char* codice, char* cognome, char* nome, char* categoria, char* data_nascita, int ore_settimanali);
void stampaAtleta(Atleta atleta, FILE *fp);
int cmpAtleti(Atleta A, Atleta B, Metodo metodo, CheckType condizione);
void liberaAtleta(Atleta atleta);
#endif