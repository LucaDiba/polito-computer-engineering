#include "esercizi.h"
#include "esercizio.h"


TabEsercizi inizializzaTabEsercizi(){
    TabEsercizi tab_esercizi = malloc(sizeof(*tab_esercizi));
    return tab_esercizi;
}
TabEsercizi leggiEsercizi(char *nome_file){
    int i;
    char buff[MAX_CHAR_ESERCIZI+1];
    FILE *fp = NULL;
    Esercizio *esercizi = NULL;
    TabEsercizi tab_esercizi = inizializzaTabEsercizi();


    if((fp=fopen(nome_file, "r")) == NULL)exit(-1);
    fscanf(fp, "%d", &(tab_esercizi->n));
    esercizi = malloc(tab_esercizi->n * sizeof(Esercizio));
    for(i=0; i<tab_esercizi->n; i++){
        //ID esercizio
        esercizi[i].id = i;
        //Nome esercizio
        fscanf(fp, "%*c%s", buff);
        esercizi[i].nome = strdup(buff);
        //Categoria
        fscanf(fp, "%s", buff);
        esercizi[i].categoria = strdup(buff);
        //Tipologia
        fscanf(fp, "%s", buff);
        esercizi[i].tipo = strdup(buff);
    }
    tab_esercizi->vettEsercizi = esercizi;
    fclose(fp);
    return tab_esercizi;
}
