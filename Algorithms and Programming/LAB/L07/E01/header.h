#ifndef E01_HEADER_H
#define E01_HEADER_H

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <limits.h>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef CHAR_MAX
#define CHAR_MAX 20
#endif
typedef struct{
    char *nome;
    int abitanti, distanza_inizio_via; //abitanti in migliaia
} Citta;
typedef Citta Item;
typedef struct{
    int *distanza_da;
} Distanza;
typedef struct{
    int *id_citta, som_dist;
} Soluzione;


void Merge(Item *A, Item *B, int l, int q, int r);
void MergeSortR(Item *A, Item *B, int l, int r);
void MergeSort(Item *A, int N);

int leggiFile(char *nome_file, Citta **passed_citta);
void generaDistanzeTraCitta(Citta *citta, int n_citta, Distanza **passed_distanze);
int calcolaDistanzaTraCitta(int id_citta_1, int id_citta_2, Distanza *distanze);
int calcolaSomDist(int *sedi_ato, Citta *citta, int n_citta, int n_ato, Distanza *distanze);
void comb(int pos, int *sol, int n, int k, int start, Soluzione *soluzione_attuale, Citta *citta, Distanza *distanze);
Soluzione calcolaCittaOttimali(Citta *citta, int n_citta, Distanza *distanze, int n_ato);
void stampaSoluzione(Citta *citta, int k, Soluzione soluzione);

#endif //E01_HEADER_H