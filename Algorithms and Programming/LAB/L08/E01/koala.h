#ifndef _KOALA_H
#define _KOALA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int **famiglie_nemiche, n;
} *TabFamiglie;

typedef struct{
	int *id_alberi_ammessi, n_alberi_ammessi;
	int id_famiglia;
} Koala;

typedef struct{
	Koala *koala;
	int n;
} *TabKoala;
typedef struct{
	int habitat, famiglie;
} Vincoli;

TabFamiglie acquisisciFamiglie(char *fam_filename, char *nem_filename, TabKoala);

TabKoala acquisisciKoala(char *filename);
void determinaAllocazione(int max_per_albero, TabKoala, TabFamiglie, Vincoli);

#endif