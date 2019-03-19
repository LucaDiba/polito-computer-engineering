#include "header.h"

void MergeSort(Item *A, int N){
    int l=0, r=N-1;
    Item *B = (Item *)malloc(N * sizeof(Item));
    MergeSortR(A, B, l, r);
}
void MergeSortR(Item *A, Item *B, int l, int r){
    int q = (l + r)/2;
    if (r <= l)
        return;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
}
void Merge(Item *A, Item *B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (A[i].distanza_inizio_via <= A[j].distanza_inizio_via)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}

int leggiFile(char *nome_file, Citta **passed_citta){
    Citta *citta = NULL;
    int n_citta,i;
    FILE *fp=NULL;
    char buff[CHAR_MAX+1];
    if((fp=fopen(nome_file, "r")) == NULL)return -1;
    fscanf(fp, "%d", &n_citta);
    citta = malloc(n_citta * sizeof(Citta));
    for(i=0; i<n_citta; i++) {
        fscanf(fp, "%*c%s %d %d", buff, &citta[i].abitanti, &citta[i].distanza_inizio_via);
        citta[i].nome = malloc(strlen(buff) + 1);
        strcpy(citta[i].nome, buff);
    }
    MergeSort(citta, n_citta);
    *passed_citta = citta;
    return n_citta;
}

void generaDistanzeTraCitta(Citta *citta, int n_citta, Distanza **passed_distanze){
    Distanza *distanze = NULL;
    int i,j,tmp_j;

    distanze = malloc((n_citta-1) * sizeof(Distanza));
    for(i=0; i<n_citta-1; i++){
        distanze[i].distanza_da = malloc( (n_citta - (i+1)) * sizeof(int));
        for(j=i+1; j<n_citta; j++){
            tmp_j = j-(i+1);
            distanze[i].distanza_da[tmp_j] = abs(citta[i].distanza_inizio_via - citta[j].distanza_inizio_via);
        }
    }
    *passed_distanze = distanze;
}

int calcolaDistanzaTraCitta(int id_citta_1, int id_citta_2, Distanza *distanze){
    int pos_citta_2;

    if(id_citta_1 > id_citta_2)
        id_citta_2 = id_citta_1 + id_citta_2 - (id_citta_1 = id_citta_2);
    pos_citta_2 = id_citta_2 - (id_citta_1+1);
    return distanze[id_citta_1].distanza_da[pos_citta_2];
}

int calcolaSomDist(int *sedi_ato, Citta *citta, int n_citta, int n_ato, Distanza *distanze){
    int i, tmp_dist_ato1, tmp_dist_ato2, id_sede_prossima_ato= 1,
        id_citta_ultima_ato, id_citta_prossima_ato, somm_dist=0;

    id_citta_ultima_ato = sedi_ato[0];
    id_citta_prossima_ato = (id_sede_prossima_ato < n_ato) ? sedi_ato[id_sede_prossima_ato++] : -1;
    for(i=0; i<n_citta; i++){
        if(i == id_citta_prossima_ato){
            id_citta_ultima_ato = id_citta_prossima_ato;
            id_citta_prossima_ato = (id_sede_prossima_ato < n_ato) ? sedi_ato[id_sede_prossima_ato++] : -1;
        }else if(i != id_citta_ultima_ato){
            tmp_dist_ato1 = calcolaDistanzaTraCitta(i, id_citta_ultima_ato, distanze);
            if(id_citta_prossima_ato != -1) {
                tmp_dist_ato2 = calcolaDistanzaTraCitta(i, id_citta_prossima_ato, distanze);
                somm_dist += citta[i].abitanti * min(tmp_dist_ato1, tmp_dist_ato2);
            }else
                somm_dist += citta[i].abitanti * tmp_dist_ato1;
        }
    }
    return somm_dist;
}

void comb(int pos, int *sol, int n, int k, int start, Soluzione *soluzione_attuale, Citta *citta, Distanza *distanze) {
    int i, som_dist;

    if (pos >= k) {
        som_dist = calcolaSomDist(sol, citta, n, k, distanze);
        if(som_dist > soluzione_attuale->som_dist)
            return;
        soluzione_attuale->som_dist = som_dist;
        for(i=0; i<k; i++)
            soluzione_attuale->id_citta[i] = sol[i];
        return;
    }
    for (i = start; i < n; i++) {
        sol[pos] = i;
        comb(pos + 1, sol, n, k, i + 1, soluzione_attuale, citta, distanze);
    }
}

Soluzione calcolaCittaOttimali(Citta *citta, int n_citta, Distanza *distanze, int n_ato){
    Soluzione soluzione;
    int *sol;

    sol = calloc((size_t)n_ato, sizeof(int));
    soluzione.id_citta = calloc((size_t)n_citta, sizeof(int));
    soluzione.som_dist = INT_MAX;
    comb(0, sol, n_citta, n_ato, 0, &soluzione, citta, distanze);
    return soluzione;
}

void stampaSoluzione(Citta *citta, int k, Soluzione soluzione){
    int i;
    for(i=0; i<k; i++)
        printf("Citta' %d: %s\n", i+1, citta[soluzione.id_citta[i]]);
    printf("Valore sommatoria: %d", soluzione.som_dist);
}