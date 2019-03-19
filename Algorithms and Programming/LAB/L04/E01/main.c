#include <stdio.h>
#include "header.h"

int main(){
    int nr=-1, nc, i,j,n=1,tmp_b,tmp_h,tmp_area, A[MAX_R][MAX_C];

    leggiMatrice(A,MAX_R,&nr,&nc);
    if(nr==-1)return -1;

    for(i=0;i<nr;i++)
        for(j=0;j<nc;j++)
            if (riconosciRegione(A, nr, nc, i, j, &tmp_b, &tmp_h)){
                tmp_area = tmp_b * tmp_h;
                printf("Regione %d: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", n++, i, j, tmp_b, tmp_h, tmp_area);
            }

    return 0;
}