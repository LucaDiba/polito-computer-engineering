#include "esercizi.h"

Esercizio EsercizioNULL(){
    Esercizio esercizio;
    esercizio.id = -1;
    return esercizio;
}
int isEsercizioNULL(Esercizio esercizio){
    return (esercizio.id == -1) ? 1 : 0;
}

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
void stampaElencoEsercizi(TabEsercizi tab_esercizi){
    int i;
    Esercizio *esercizi = tab_esercizi->vettEsercizi;
    for(i=0; i < tab_esercizi->n; i++)
        stampaEsercizio(esercizi[i]);
}
void stampaEsercizio(Esercizio esercizio){
    printf("%s\n"
                   "\tCategoria: %s\n"
                   "\tTipo: %s\n", esercizio.nome, esercizio.tipo, esercizio.categoria);
}
Esercizio cercaEsercizio(char *nome_esericizio, TabEsercizi tab_esercizi){
    int i;
    Esercizio *esercizi = tab_esercizi->vettEsercizi;
    for(i=0; i<tab_esercizi->n; i++){
        if(strcmp(esercizi[i].nome, nome_esericizio) == 0)
            return esercizi[i];
    }
    return EsercizioNULL();
}
Esercizio getEsercizioById(int id_esercizio, TabEsercizi tab_esercizi){
    int i;
    Esercizio *esercizi = tab_esercizi->vettEsercizi;
    for(i=0; i<tab_esercizi->n; i++){
        if(esercizi[i].id == id_esercizio)
            return esercizi[i];
    }
    return EsercizioNULL();
}