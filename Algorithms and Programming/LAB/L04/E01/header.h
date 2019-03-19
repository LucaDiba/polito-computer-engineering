#ifndef E01_HEADER_H
#define E01_HEADER_H

#define MAX_R 50
#define MAX_C 50
void leggiMatrice(int M[][MAX_C], int max_r, int *nr, int *nc){
    int i,j;
    FILE *fp = NULL;
    fp = fopen("file.txt", "r");
    if(fp == NULL)return;
    fscanf(fp, "%d %d%*c", nr, nc);
    if(*nr > max_r){
        *nr = -1;
        return;
    }

    for(i=0; i < *nr; i++)
        for(j=0; j < *nc; j++)
            fscanf(fp, "%d", &M[i][j]);
    fclose(fp);
}
int riconosciRegione(int A[][MAX_C], int nr, int nc, int i, int j, int *b, int *h){
    int tmp_area, k,l,terminato, val_su, val_sx;
    /* valori superiore e sinistro
     * se:
     *    - ci si trova in prossimità del bordo superiore o sinistro
     *  oppure
     *    - la casella precedente è "0"
     *  allora sicuramente questa casella sarà la prima a partire, rispettivamente, da sopra o da sx
     */
    val_su = (i==0) ? 1 : !A[i-1][j];
    val_sx = (j==0) ? 1 : !A[i][j-1];
    if(A[i][j] == 1 && val_su && val_sx){
        tmp_area = 0;
        k=i;
        l=j;
        terminato = 0;
        while(terminato == 0){
            if(A[k][l] == 1 && l < nc){
                A[k][l] = 0;
                l++;
                tmp_area++;
            }else if(k+1 < nr && A[k+1][j] == 1){ //continua sotto
                k++;
                l=j;
            }else{ //rettangolo terminato
                terminato = 1;
                *h = k-i+1;
                *b = tmp_area/(*h);
            }
        }
        return 1;
    }
    return 0;
}
#endif //E01_HEADER_H
