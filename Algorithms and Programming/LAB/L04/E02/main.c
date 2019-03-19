#include <stdio.h>
#include <string.h>
#include "header.h"

int main() {
    int nr,np;
    char pagina[MAXR][MAXC], *parole[MAXP], cerca[MAXC];

    nr = leggiPagina(pagina,MAXR);
    if(nr == -1)return -1;
    np = riconosciParole(pagina,nr,parole,MAXP);
    InsertionSort(parole, 0, np-1);

    while(scanf("%s", cerca) > 0) {
        if(strcmp(cerca, "$fine")==0)break;
        TrovaParola(parole, (int)&pagina[0][0], cerca, np);
    }
    return 0;
}