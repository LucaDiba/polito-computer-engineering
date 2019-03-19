#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include "PQ.h"

typedef Item coordinate_t;
typedef struct labirinto_t_s{
    char **labirinto;
    int **d;
    coordinate_t **st;
    int nr, nc;
} *labirinto_t;

labirinto_t labirintoINIT();
labirinto_t leggiFile(FILE *fp);
void        labirintoFREE       (labirinto_t labirinto);
void        esploraCoordinate   (labirinto_t labirinto, PQ pq, coordinate_t coord, coordinate_t coord_exp);
void        LABIRINTOspD        (labirinto_t labirinto);
void        stampaCamminoMinimoR(labirinto_t labirinto, coordinate_t coord);
void        stampaCamminoMinimo (labirinto_t labirinto);

int main(){
    labirinto_t labirinto;
    FILE *fp = NULL;
    int i, j;

    if((fp=fopen("labirinto.txt", "r")) == NULL)
        return EXIT_FAILURE;
    labirinto = leggiFile(fp);

    LABIRINTOspD(labirinto);
    printf("\n\nCammino minimo trovato: ");
    stampaCamminoMinimo(labirinto);

    labirintoFREE(labirinto);
    return 0;
}

labirinto_t labirintoINIT(){
    return malloc(sizeof(struct labirinto_t_s));
}

void labirintoFREE(labirinto_t labirinto){
    int i;
    for(i=0; i<labirinto->nr; i++) {
        free(labirinto->labirinto[i]);
        free(labirinto->d [i]);
        free(labirinto->st[i]);
    }
    free(labirinto->labirinto);
    free(labirinto->d);
    free(labirinto->st);
    free(labirinto);
}

labirinto_t leggiFile(FILE *fp){
    labirinto_t labirinto = labirintoINIT();
    char **matr;
    int i, nr, nc;

    fscanf(fp, "%d %d", &nr, &nc);
    matr = malloc(nr * sizeof(char*));
    labirinto->st = malloc(nr * sizeof(coordinate_t*));
    labirinto->d  = malloc(nr * sizeof(int*));
    for(i=0; i<nr; i++){
        matr[i] = malloc( (nc+1) * sizeof(char));
        labirinto->st[i] = malloc( nc * sizeof(coordinate_t));
        labirinto->d [i] = malloc( nc * sizeof(int));
        fscanf(fp, " %s", matr[i]);
    }

    labirinto->labirinto = matr;
    labirinto->nr = nr;
    labirinto->nc = nc;
    return labirinto;
}

void esploraCoordinate(labirinto_t labirinto, PQ pq, coordinate_t coord, coordinate_t coord_exp){
    if(labirinto->labirinto[coord_exp.r][coord_exp.c] != 'X'){
        if(labirinto->d[coord.r][coord.c] + 1 < labirinto->d[coord_exp.r][coord_exp.c]){
            labirinto->d[coord_exp.r][coord_exp.c] = labirinto->d[coord.r][coord.c] + 1;
            PQchange(pq, labirinto->d, coord_exp);
            labirinto->st[coord_exp.r][coord_exp.c] = coord;
        }
    }
}

void LABIRINTOspD(labirinto_t labirinto){
    int flag=0, i, j, i_start=-1, j_start=-1, v, w;
    coordinate_t coord, coord_exp;
    PQ pq = PQinit(labirinto->nr * labirinto->nc);

    // Trova punto di partenza e setta st e d
    for(i=0; i<labirinto->nr; i++) {
        for (j = 0; j < labirinto->nc; j++) {
            if (labirinto->labirinto[i][j] == 'I') {
                i_start = i;
                j_start = j;
            }
            // Se non e` muro
            if (labirinto->labirinto[i][j] != 'X') {
                labirinto->st[i][j].r = -1;
                labirinto->st[i][j].c = -1;
                labirinto->d[i][j] = INT_MAX;
                coord.r = i;
                coord.c = j;
                PQinsert(pq, labirinto->d, coord);
            }
        }
    }
    if(i_start == -1 || j_start == -1){
        printf("Inizio non trovato");
        exit(EXIT_FAILURE);
    }
    i=i_start;
    j=j_start;
    labirinto->st[i][j].r = i;
    labirinto->st[i][j].c = j;
    labirinto->d[i][j] = 0;
    PQchange(pq, labirinto->d, labirinto->st[i][j]);

    while(!PQempty(pq)){
        coord = PQextractMin(pq, labirinto->d);
        if(labirinto->d[coord.r][coord.c] != INT_MAX){
            if(coord.r > 0){ // Esplora sopra
                coord_exp.r = coord.r - 1;
                coord_exp.c = coord.c;
                esploraCoordinate(labirinto, pq, coord, coord_exp);
            }
            if(coord.r < labirinto->nr - 1){ // Esplora sotto
                coord_exp.r = coord.r + 1;
                coord_exp.c = coord.c;
                esploraCoordinate(labirinto, pq, coord, coord_exp);
            }
            if(coord.c > 0){ // Esplora sx
                coord_exp.r = coord.r;
                coord_exp.c = coord.c - 1;
                esploraCoordinate(labirinto, pq, coord, coord_exp);
            }
            if(coord.c < labirinto->nc - 1){ // Esplora dx
                coord_exp.r = coord.r;
                coord_exp.c = coord.c + 1;
                esploraCoordinate(labirinto, pq, coord, coord_exp);
            }
        }
    }
}

void stampaCamminoMinimoR(labirinto_t labirinto, coordinate_t coord){
    if(labirinto->labirinto[coord.r][coord.c] == 'I')
        return;

    stampaCamminoMinimoR(labirinto, labirinto->st[coord.r][coord.c]);
    printf("<%2d, %2d> ", coord.r, coord.c);
}

void stampaCamminoMinimo(labirinto_t labirinto){
    int flag=0,i, j;
    coordinate_t coord;
    for(i=0; i<labirinto->nr && flag==0; i++)
        for (j=0; j < labirinto->nc && flag==0; j++)
            if(labirinto->labirinto[i][j] == 'F')
                flag=1;
    if(flag == 0){
        printf("Fine non trovata");
        exit(EXIT_FAILURE);
    }
    coord.r = --i;
    coord.c = --j;
    stampaCamminoMinimoR(labirinto, coord);
}