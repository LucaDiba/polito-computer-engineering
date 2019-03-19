#include <stdio.h>
#include <stdlib.h>
#include "sequenze.h"

TabSequenza leggiFrecce(char* nome_file){
	TabSequenza tab_sequenza;
	int i;
	char *vett;
	FILE *fp=NULL;

	tab_sequenza = malloc(sizeof(*tab_sequenza));

	if((fp=fopen(nome_file, "r")) == NULL)
		exit(EXIT_FAILURE);

	fscanf(fp, "%d", &(tab_sequenza->n));
	tab_sequenza->seq = malloc(tab_sequenza->n * sizeof(int));
	for(i=0; i<tab_sequenza->n; i++){
		fscanf(fp, " %d", &(tab_sequenza->seq[i]));
	}
	fclose(fp);
	return tab_sequenza;
}

int daCambiarePerValidare(TabSequenza tab_sequenza){
    int i, j, a, b, dx, sx, da_cambiare = 0, count = 0;

    for(i = 0, j = 1; j < tab_sequenza->n; i++, j++) {
        //Cerca scontro
        if(tab_sequenza->seq[i] == ARROW_R && tab_sequenza->seq[j] == ARROW_L) {
            dx = sx = 0;

            for (a = i; a >= 0 && tab_sequenza->seq[a] == 0; dx++, a--, count++);
            for (b = j; b < tab_sequenza->n && tab_sequenza->seq[b] == 1; sx++, b++, count++);

            if (sx != dx)
                da_cambiare += abs(sx-dx);

            j = b, i = b - 1;
        }
    }

    return da_cambiare/2;
}

int validaSoluzione(int* sol, TabSequenza tab_sequenza){
    int i, da_cambiare;
    TabSequenza tab_sequenza_tmp = malloc(sizeof(*tab_sequenza_tmp));
    tab_sequenza_tmp->seq = malloc(sizeof(int) * tab_sequenza->n);
    tab_sequenza_tmp->n = tab_sequenza->n;

    for(i=0; i<tab_sequenza->n; i++){
        if(sol[i] == 1)
            tab_sequenza_tmp->seq[i] = (tab_sequenza->seq[i] == ARROW_L) ? ARROW_R : ARROW_L;
        else
            tab_sequenza_tmp->seq[i] = (tab_sequenza->seq[i] == ARROW_L) ? ARROW_L : ARROW_R;
    }

    da_cambiare = daCambiarePerValidare(tab_sequenza_tmp);

    free(tab_sequenza_tmp->seq);
    free(tab_sequenza_tmp);

    return (da_cambiare == 0) ? 1 : 0;
}

int perm_r(int pos, int *dist_val, int *sol, int *mark, int n_dist, int count, TabSequenza tab_sequenza) {
    int i;
    if (pos >= tab_sequenza->n && validaSoluzione(sol, tab_sequenza)){
        for (i=0; i<tab_sequenza->n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            count=perm_r(pos+1,dist_val,sol,mark,n_dist,count,tab_sequenza);
            mark[i]++;
        }
    }
    return count;
}

int cambia(int da_cambiare, TabSequenza tab_sequenza){
	int dist_val[2] = {0,1}, *sol, mark[2];

    mark[0] = tab_sequenza->n - da_cambiare;
    mark[1] = da_cambiare;
    sol = malloc(tab_sequenza->n * sizeof(int));

	return perm_r(0, dist_val, sol, mark, 2, 0, tab_sequenza);
}