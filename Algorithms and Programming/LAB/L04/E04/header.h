#ifndef E04_HEADER_H
#define E04_HEADER_H

int somma_t(int n, int m){
    int k;
    if(n/10 == 0)
        return m+n;
    k = n/10*10;
    return somma_t(n/10, m+n-k);
}
int somma(int n){
    return somma_t(n, 0);
}

#endif //E04_HEADER_H