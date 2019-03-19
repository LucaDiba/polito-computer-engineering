#ifndef E02_HEADER_H
#define E02_HEADER_H

#include <ctype.h>
#define MAXC 80
#define MAXR 60
#define MAXP 1000
typedef char *Item;

int strcmpF(char *A, char *B);
int leggiPagina(char pagina[][MAXC], int max_r);
int riconosciParole(char pagina[][MAXC], int nr, char *parole[], int max_p);
int less(Item A, Item B);
int isequal(Item A, Item B);
void InsertionSort(Item A[], int l, int r);
int BinSearch(Item v[], int l, int r, Item k);
void TrovaParola(char *parole[], int page_start_address, char *cerca, int np);

int strcmpF(char *A, char *B){
    int i, tmp, finito=0;
    for(i=0; !finito; i++){
        tmp = tolower(A[i]) - tolower(B[i]);
        if(!isalnum(A[i]) && !isalnum(B[i])) finito=1;
        else if(tmp != 0) return tmp;
    }
    return 0;
}
int leggiPagina(char pagina[][MAXC], int max_r){
    FILE *fp=NULL;
    int i;
    for(i=0;i<MAXC*MAXR; i++)pagina[0][i]='\0';
    i=0;
    if((fp=fopen("sequenze.txt", "r")) == NULL)return -1;
    while(fgets(pagina[i], MAXC, fp) != NULL && i < max_r)i++;
    fclose(fp);
    return i;
}
int riconosciParole(char pagina[][MAXC], int nr, char *parole[], int max_p){
    int i,j,k=0,parola_iniziata = 0;
    char tmp_char;

    for(i=0; i<nr && k < max_p; i++) {
        for(j=0; j<MAXC; j++){
            tmp_char = pagina[i][j];
            if(!isalnum(tmp_char)) {
                parola_iniziata = 0;
                if(tmp_char == '\n')
                    break;
            }else{
                if(parola_iniziata == 0){
                    parole[k++] = &pagina[i][j];
                    parola_iniziata = 1;
                }
            }
        }
    }
    return k;
}
int less(Item A, Item B){
    return (strcmpF(A, B) < 0);
}
int isequal(Item A, Item B){
    return (strcmpF(A, B) == 0);
}
void InsertionSort(Item A[], int l, int r){
    int i, j;
    Item x;
    for (i = l + 1; i <= r; i++) {
        x = A[i];
        j = i - 1;
        while (j >= l && less(x, A[j])) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}
int BinSearch(Item v[], int l, int r, Item k){
    int m;
    if((r-l) == 0)
        if(isequal(v[l], k))
            return(l);
        else
            return(-1);
    m = (l+r) / 2;
    if(!less(v[m], k))
        return(BinSearch(v, l, m, k));
    else
        return(BinSearch(v, m+1, r, k));
}
void TrovaParola(char *parole[], int page_start_address, char *cerca, int np){
    int n,n_lettera,num_riga,num_colonna,virgola=1;

    n=BinSearch(parole, 0, np-1, cerca);
    if(n == -1){
        printf("Parola non trovata");
        return;
    }
    printf("Parola %s trovata in: ", cerca);
    while(strcmpF(parole[n-1], cerca)==0)n--;
    for(; strcmpF(parole[n], cerca)==0; n++) {
        if(virgola==1)virgola++;else printf(", ");
        n_lettera = (int) parole[n] - page_start_address;
        num_colonna = n_lettera % MAXC;
        num_riga = (n_lettera - num_colonna) / MAXC;
        printf("(%d, %d)", num_riga, num_colonna);
    }
    printf(".");
}

#endif //E02_HEADER_H
