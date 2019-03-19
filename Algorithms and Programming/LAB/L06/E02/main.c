#include <stdio.h>
#include "header.h"

int main(){
    Categoria *categorie;
    Atleta *atleti;
    n_Info n_info;
    AtletaOrder orderby;
    Ordered isOrdered;
    int i;
    char buff[N_MAX+1];

    if((n_info = leggiFile(&atleti, &categorie, &orderby)).n_atleti == 0){
        printf("File non letto o nessun atleta presente");
        return 0;
    }

    isOrdered.byDataNascita=0;
    isOrdered.byCodice=0;
    isOrdered.byCognome=0;
    isOrdered.byCategoria=0;

    while(1) {
        fseek(stdin,0,SEEK_END);
        i=0;
        printf("\nEFFETTUA UNA SCELTA:\n"
                       "%d. stampa anagrafica\n"
                       "%d. stampa per data di nascita\n"
                       "%d. stampa per codice\n"
                       "%d. stampa per cognome\n"
                       "%d. stampa atleti per categoria\n"
                       "%d. aggiornamento monte ore settimanali\n"
                       "%d. ricerca atleta per codice\n"
                       "%d. ricerca atleta per cognome\n"
                       "%d. esci\n"
                       "Codice selezione: ", c_stampa_elenco, c_order_bydatanascita, c_order_bycodice,
               c_order_bycognome, c_stampa_percategoria, c_aggiornamonteore, c_search_bycodice, c_search_bycognome,
               c_exit);
        scanf("%d%*c", &i);
        if (i == c_exit)
            break;
        if (i <= c_first || i > c_exit) {
            printf("Scelta non valida");
            continue;
        }
        if (i == c_stampa_elenco) {
            stampaElenco(orderby.byAcquisizione, n_info.n_atleti, &categorie);
        } else if (i == c_order_bydatanascita) {
            if(!isOrdered.byDataNascita) {
                MergeSortAtleti(orderby.byDataNascita, n_info.n_atleti, categorie, byDataNascita);
                isOrdered.byDataNascita = 1;
            }
            stampaElenco(orderby.byDataNascita, n_info.n_atleti, &categorie);
            printf("Atleti ordinati per data di nascita");
        } else if (i == c_order_bycodice) {
            if(!isOrdered.byCodice) {
                MergeSortAtleti(orderby.byCodice, n_info.n_atleti, categorie, byCodice);
                isOrdered.byCodice = 1;
            }
            stampaElenco(orderby.byCodice, n_info.n_atleti, &categorie);
            printf("Atleti ordinati per codice identificativo");
        } else if (i == c_order_bycognome) {
            if(!isOrdered.byCognome) {
                MergeSortAtleti(orderby.byCognome, n_info.n_atleti, categorie, byCognome);
                isOrdered.byCognome = 1;
            }
            stampaElenco(orderby.byCognome, n_info.n_atleti, &categorie);
            printf("Atleti ordinati per cognome");
        } else if (i == c_stampa_percategoria) {
            if(!isOrdered.byCategoria) {
                MergeSortAtleti(orderby.byCategoria, n_info.n_atleti, categorie, byCategoria);
                isOrdered.byCategoria = 1;
            }
            stampaCategorie(orderby.byCategoria, categorie, n_info);
        } else if (i == c_aggiornamonteore) {
            printf("Inserisci codice atleta da aggiornare: ");
            scanf("%s", buff);
            if(!isOrdered.byCodice) {
                MergeSortAtleti(orderby.byCodice, n_info.n_atleti, categorie, byCodice);
                isOrdered.byCodice = 1;
            }
            i = BinSearch(orderby.byCodice, n_info.n_atleti, buff, byCodice);
            if (i == -1)
                printf("Nessun risultato");
            else
                aggiornaMonteOre(atleti, i);
        } else if (i == c_search_bycodice) {
            printf("Inserisci codice da cercare: ");
            scanf("%s", buff);
            if(!isOrdered.byCodice) {
                MergeSortAtleti(orderby.byCodice, n_info.n_atleti, categorie, byCodice);
                isOrdered.byCodice = 1;
            }
            i = BinSearch(orderby.byCodice, n_info.n_atleti, buff, byCodice);
            if (i == -1)
                printf("Nessun risultato");
            else
                stampaAtleta(&(atleti[i]), &categorie, stdout);
        } else if (i == c_search_bycognome) {
            printf("Inserisci cognome (anche parziale) da cercare: ");
            scanf("%s", buff);
            if(!isOrdered.byCognome) {
                MergeSortAtleti(orderby.byCognome, n_info.n_atleti, categorie, byCognome);
                isOrdered.byCognome = 1;
            }
            i = BinSearch(orderby.byCognome, n_info.n_atleti, buff, byCognome);
            if (i == -1)
                printf("Nessun risultato");
            else
                stampaAtleta(&(atleti[i]), &categorie, stdout);
        }
    }
    return 0;
}