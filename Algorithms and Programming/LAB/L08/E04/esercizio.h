#ifndef _ESERCIZI_H
#define _ESERCIZI_H

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include <string.h>

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
//Esercizi
typedef struct s_Esercizio* Esercizio;

Esercizio EsercizioNULL();
int isEsercizioNULL(Esercizio esercizio);

#endif //_ESERCIZI_H