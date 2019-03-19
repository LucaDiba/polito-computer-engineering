#ifndef _ESERCIZI_H
#define _ESERCIZI_H

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include <string.h>

#include "esercizio.h"

#ifndef t_string
    #define t_string
    typedef char* string;
#endif
#ifndef t_data
    #define t_data
    typedef struct{
	    int giorno, mese, anno, timestamp;
	} Data;
#endif

#define MAX_CHAR_ESERCIZI 50

typedef struct s_TabEsercizi *TabEsercizi;

TabEsercizi leggiEsercizi(string nome_file);
void stampaEsercizio(Esercizio esercizio);
void stampaElencoEsercizi(TabEsercizi tabEsercizi);

Esercizio cercaEsercizio(string nome_esericizio, TabEsercizi tab_esercizi);
int getEsercizioId(Esercizio);
Esercizio getEsercizioById(int id_esercizio, TabEsercizi tab_esercizi);

#endif //_ESERCIZI_H