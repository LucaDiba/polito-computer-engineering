#include "esercizi_array.h"
#include "esercizio.h"

struct s_TabEsercizi{
    int n;
    Esercizio *vettEsercizi;
};

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
int getEsercizioId(Esercizio esercizio){
    return esercizio.id;
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