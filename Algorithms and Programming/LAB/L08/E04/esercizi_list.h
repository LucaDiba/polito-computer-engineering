#ifndef _ESERCIZI_LIST_H
#define _ESERCIZI_LIST_H

#include "atleti_lista.h"
#include "esercizi_array.h"

typedef struct s_EsercizioPiano EsercizioPiano;

// Gestione piani esercizi
void leggiPiani(TabAtleti, TabEsercizi);
void stampaPiano(char* codice_atleta, TabAtleti, TabEsercizi);
void aggiungiEsercizioPiano(char* codice_atleta, TabAtleti, TabEsercizi);
void modificaEsercizioPiano(char* nome_esercizio, Atleta, TabEsercizi);
void liberaPiano(EsercizioPiano*);

#endif //_ESERCIZI_LIST_H