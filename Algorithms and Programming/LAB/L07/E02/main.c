#include <stdio.h>
#include "header.h"
#include "atleti.h"
#include "esercizi.h"

typedef enum{
    c_first, c_stampa_elenco, c_stampa_percategoria, c_stampa_esercizi, c_stampa_piano, c_aggiornamonteore, c_search_bycodice, c_search_bycognome, c_atleta_add, c_atleta_del, c_exit
} Comandi;

int main(){
    Categoria *categorie;
    n_Info n_info;  
    TabAtleti tab_atleti;
    Item* tmp_item;
    TabEsercizi tab_esercizi;
    int i, sizeof_categorie = CATEGORIE_INIZIALI;
    char buff[N_MAX+1];

    if((n_info = leggiFile(&tab_atleti, &categorie, &sizeof_categorie)).n_atleti == 0){
        printf("File non letto o nessun atleta presente");
        return 0;
    }
    if(!leggiEsercizi("esercizi.txt", &tab_esercizi)){
        printf("File esercizi impossibile da leggere");
        return -1;
    }
    leggiPiani(tab_atleti, tab_esercizi);

    while(1) {
        fseek(stdin,0,SEEK_END);
        i=0;
        printf("\nEFFETTUA UNA SCELTA:\n"
                       "%d. stampa anagrafica\n"
                       "%d. stampa atleti per categoria\n"
                       "%d. stampa esercizi disponibili\n"
                       "%d. stampa piano atleta\n"
                       "%d. aggiornamento monte ore settimanali\n"
                       "%d. ricerca atleta per codice\n"
                       "%d. ricerca atleta per cognome\n"
                       "%d. aggiungi atleta\n"
                       "%d. cancella atleta\n"
                       "%d. esci\n"
                       "Codice selezione: ", c_stampa_elenco, c_stampa_percategoria, c_stampa_esercizi, c_stampa_piano, c_aggiornamonteore,
               c_search_bycodice, c_search_bycognome, c_atleta_add, c_atleta_del, c_exit);
        scanf("%d%*c", &i);
        if (i == c_exit)
            break;
        if (i <= c_first || i > c_exit) {
            printf("Scelta non valida");
            continue;
        }
        if (i == c_stampa_elenco) {
            stampaElenco(tab_atleti.head, &categorie);
        } else if (i == c_stampa_percategoria){
            stampaCategorie(categorie, n_info.n_categorie);
        } else if (i == c_stampa_esercizi){
            stampaEsercizi(tab_esercizi);
        } else if (i == c_stampa_piano){
            printf("Inserisci cognome atleta del quale si vuole conoscere il piano: ");
            scanf("%s", buff);
            stampaPiano(tab_atleti, buff);
        } else if (i == c_aggiornamonteore) {
            printf("Inserisci codice atleta da aggiornare: ");
            scanf("%s", buff);
            tmp_item = listSearch(tab_atleti.head, buff, byCodice);
            if (tmp_item == NULL)
                printf("Nessun risultato");
            else
                aggiornaMonteOre(tmp_item);
        } else if (i == c_search_bycodice) {
            printf("Inserisci codice atleta da cercare: ");
            scanf("%s", buff);
            tmp_item = listSearch(tab_atleti.head, buff, byCodice);
            if (tmp_item == NULL)
                printf("Nessun risultato");
            else
                stampaAtleta(tmp_item, &categorie, stdout);
        } else if (i == c_search_bycognome) {
            printf("Inserisci cognome atleta da cercare: ");
            scanf("%s", buff);
            tmp_item = listSearch(tab_atleti.head, buff, byCognome);
            if (tmp_item == NULL)
                printf("Nessun risultato");
            else
                stampaAtleta(tmp_item, &categorie, stdout);
        } else if (i == c_atleta_add) {
            aggiungiAtleta(&tab_atleti, &n_info, categorie, &sizeof_categorie);
        } else if (i == c_atleta_del) {
            printf("Inserisci codice atleta da eliminare: ");
            scanf("%s", buff);
            cancellaAtleta(&tab_atleti, buff, categorie);
        }
    }
    return 0;
}