#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"

struct pqueue { Item *array; int heapsize; };

int LEFT(int i){
    return i*2+1;
}

int RIGHT(int i) {
    return i*2+2;
}

int PARENT(int i) {
    return (i-1)/2;
}

PQ PQinit(int maxN){
    PQ pq;
    pq = malloc(sizeof(*pq));
    pq->array = (Item *)malloc(maxN*sizeof(Item));
    pq->heapsize = 0;
    return pq;
}

int PQempty(PQ pq) {
    return PQsize(pq) == 0;
}

int PQsize(PQ pq) {
    return pq->heapsize;
}

void PQinsert (PQ pq, Item item) {
    int i;
    i  = pq->heapsize++;
    while( (i>=1) && (ITEMgreater(pq->array[PARENT(i)], item)) ) {
        pq->array[i] = pq->array[PARENT(i)];
        i = (i-1)/2;
    }
    pq->array[i] = item;
}

void PQadd(PQ pq){
    Item partecipante;

    partecipante = ITEMscan();
    PQinsert(pq, partecipante);
}

void Swap(PQ pq, int n1, int n2) {
    Item temp;

    temp  = pq->array[n1];
    pq->array[n1] = pq->array[n2];
    pq->array[n2] = temp;
}


void Heapify(PQ pq, int i) {
    int l, r, smallest;
    l = LEFT(i);
    r = RIGHT(i);
    if ( (l < pq->heapsize) && (ITEMless(pq->array[l], pq->array[i])) )
        smallest = l;
    else
        smallest = i;
    if ( (r < pq->heapsize) && (ITEMless(pq->array[r], pq->array[smallest])))
        smallest = r;
    if (smallest != i) {
        Swap(pq, i,smallest);
        Heapify(pq, smallest);
    }
}

Item PQextractMin(PQ pq) {
    Item item;
    Swap (pq, 0,pq->heapsize-1);
    item = pq->array[pq->heapsize-1];
    pq->heapsize--;
    Heapify(pq, 0);
    return item;
}

Item PQshowMin(PQ pq) {
    return pq->array[0];
}

void PQStampaRanking(PQ pq, FILE* fp) {
    int i, j, tmp_max, tmp_max_id, *stampati;
    stampati = calloc(PQsize(pq), sizeof(int));

    // stampa ranking
    for (i = 0; i < pq->heapsize; i++, printf("\n")){
        tmp_max = -1;
        for (j = 0; j < pq->heapsize; j++) {
            if (stampati[j] == 0 && ITEMgetPunteggio(pq->array[j]) >= tmp_max) {
                tmp_max = ITEMgetPunteggio(pq->array[j]);
                tmp_max_id = j;
            }
        }
        ITEMshow(pq->array[tmp_max_id], fp);
        stampati[tmp_max_id] = 1;
    }
}

void PQStampa(PQ pq, FILE* fp){
    int i;
    fprintf(fp, "%d\n", PQsize(pq));
    for (i = 0; i < pq->heapsize; i++, printf("\n")) {
        ITEMshow(pq->array[i], fp);
    }
}

void PQLeggi(PQ pq, FILE* fp){
    int i, n;
    Item tmp_item;

    fscanf(fp, "%d", &n);
    for(i=0; i<n; i++){
        tmp_item = ITEMFileScan(fp);
        PQinsert(pq, tmp_item);
    }
}

void PQchange (PQ pq, int pos, Item item) {
    while( (pos>=1) && (ITEMgreater(pq->array[PARENT(pos)], item)) ) {
        pq->array[pos] = pq->array[PARENT(pos)];
        pos = (pos-1)/2;
    }
    pq->array[pos] = item;
    Heapify(pq, pos);
}

void PQdeleteItem(PQ pq, char* nome){
    int i;

    for (i = 0; i < pq->heapsize; i++)
        if(ITEMnamecmp(nome, pq->array[i]) == 0){
            Swap(pq, i, pq->heapsize-1);
            pq->heapsize--;
            Heapify(pq, 0);
        }
}