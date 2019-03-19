#include <stdio.h>
#include "sequenze.h"

int main(){
    TabSequenza tab_sequenza;
    int da_cambiare;

    tab_sequenza = leggiFrecce("seq.txt");
    da_cambiare = daCambiarePerValidare(tab_sequenza);
    printf("Da cambiare: %d frecce\n", da_cambiare);
    if(da_cambiare > 0)
        cambia(da_cambiare, tab_sequenza);
    return 0;
}