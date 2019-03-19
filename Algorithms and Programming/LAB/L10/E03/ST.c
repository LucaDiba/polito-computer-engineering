#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int N; int M;};

ST STinit(int maxN) {
    int i;
    ST st = malloc(sizeof(*st));
    if(st == NULL){
        printf("Errore allocazione ST");
        exit(EXIT_FAILURE);
    }
    st->N = 0;
    st->M = maxN;
    st->a = malloc(st->M * sizeof(Item) );
    if(st->a == NULL){
        printf("Errore allocazione ST item");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < st->M; i++)
        st->a[i] = ITEMsetvoid();
    return st;
}

int hash(Key k, int M) {
    int h = 0, base = 127;
    for ( ; *k != '\0'; k++)
        h = (base * h + *k) % M;
    return h;
}

int hash1(Key k, int M) {
    int h = 0, base = 127;
    for ( ; *k != '\0'; k++)
        h = (base * h + *k-64) % M;
    return h;
}

int hashU(Key k, int M) {
    int h, a = 31415, b = 27183;
    for ( h = 0; *k != '\0'; k++, a = a*b % (M-1))
        h = (a*h + *k) % M;
    return h;
}

int STcount(ST st) {
    return st->N;
}

int STempty(ST st) {
    if ( STcount(st) == 0)
        return 1;
    else
        return 0;
}

int full(ST st, int i) {
    if (ITEMcheckvoid(st->a[i]))
        return 0;
    else
        return 1;
}

int STinsert(ST st, Item item) {
    int i = hash1(KEYget(item), st->M);
    while (full(st, i))
        i = (i+1)%st->M;
    st->a[i] = item;
    st->N++;
    return i;
}

Item STsearch(ST st, Key k) {
    int i = hash1(k, st->M);
    while (full(st, i))
        if (KEYcompare(k, KEYget(st->a[i]))==0)
            return st->a[i];
        else
            i = (i+1)%st->M;
    return ITEMsetvoid();
}

int STsearchID(ST st, Key k) {
    int i = hash1(k, st->M);
    while (full(st, i)){
        if (KEYcompare(k, KEYget(st->a[i])) == 0)
            return i;
        else
            i = (i + 1) % st->M;
    }
    return -1;
}

void STdisplay(ST st) {
    int i;
    for (i = 0; i < st->M; i++) {
        printf("st->a[%d] = ", i);
        ITEMshow(st->a[i]);
        printf("\n");
    }
}

void STdelete(ST st, Key k) {
    int j, i = hash1(k, st->M);
    Item tmp;
    while (full(st, i))
        if (KEYcompare(k, KEYget(st->a[i]))==0)
            break;
        else
            i = (i+1) % st->M;
    if (ITEMcheckvoid(st->a[i]))
        return;
    st->a[i] = ITEMsetvoid();
    st->N--;
    for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
        tmp = st->a[j];
        st->a[j] = ITEMsetvoid();
        STinsert(st, tmp);
    }
}

Item STretrieve(ST st, int v){
    return st->a[v];
}