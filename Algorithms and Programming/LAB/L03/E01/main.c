#include <stdio.h>
#include <stdlib.h>
#define MAX_R 50
#define MAX_C 50

int main()
{
    FILE *fp=NULL;
    int nr, nc, i,j,k,l,n=1,tmp_b,tmp_h,tmp_area, A[MAX_R][MAX_C], terminato;

    fp = fopen("file.txt", "r");
    if(fp == NULL)return -1;
    fscanf(fp, "%d %d%*c", &nr, &nc);

    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            fscanf(fp, "%d", &A[i][j]);

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(A[i][j] == 1){
                tmp_area = 0;
                k=i;
                l=j;
                terminato = 0;
                while(terminato == 0){
                    if(A[k][l] == 1){
                        A[k][l] = 0;
                        l++;
                        tmp_area++;
                    }else if(k+1 < nr && A[k+1][j] == 1){ //continua sotto
                        k++;
                        l=j;
                    }else{ //rettangolo terminato
                        terminato = 1;
                        tmp_h = k-i+1;
                        tmp_b = tmp_area/tmp_h;
                        printf("Regione %d: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d\n", n,i,j,tmp_b,tmp_h,tmp_area);
                        n++;
                    }
                }
            }
        }
    }
    fclose(fp);
    return 0;
}
