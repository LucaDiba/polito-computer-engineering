#include <stdio.h>
#include "header.h"

int main(){
    Categoria *categorie;
    Atleta *atleti;
    n_Info n_info;
    Metodo ordinamentoAttuale = byAcquisizione;
    int i;
    char buff[N_MAX+1];

    if((n_info = leggiFile(&atleti, &categorie)).n_atleti == 0){
        printf("File non letto o nessun atleta presente");
        return 0;
    }

    while(1) {
        fseek(stdin,0,SEEK_END);
        i=0;
        printf("\nEFFETTUA UNA SCELTA:\n"
                       "%d. stampa anagrafica\n"
                       "%d. ordina per data di nascita\n"
                       "%d. ordina per codice\n"
                       "%d. ordina per cognome\n"
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
            stampaElenco(atleti, n_info.n_atleti, &categorie);
        } else if (i == c_order_bydatanascita) {
            MergeSortAtleti(atleti, n_info.n_atleti, categorie, byDataNascita);
            ordinamentoAttuale = byDataNascita;
            printf("Atleti ordinati per data di nascita");
        } else if (i == c_order_bycodice) {
            MergeSortAtleti(atleti, n_info.n_atleti, categorie, byCodice);
            ordinamentoAttuale = byCodice;
            printf("Atleti ordinati per codice identificativo");
        } else if (i == c_order_bycognome) {
            MergeSortAtleti(atleti, n_info.n_atleti, categorie, byCognome);
            ordinamentoAttuale = byCognome;
            printf("Atleti ordinati per cognome");
        } else if (i == c_stampa_percategoria) {
            stampaCategorie(atleti, categorie, n_info);
        } else if (i == c_aggiornamonteore) {
            printf("Inserisci codice atleta da aggiornare: ");
            scanf("%s", buff);
            i = (ordinamentoAttuale == byCodice) ? BinSearch(atleti, n_info.n_atleti, buff, byCodice) : LinSearch(
                    atleti, n_info.n_atleti, buff, byCodice);
            if (i == -1)
                printf("Nessun risultato");
            else
                aggiornaMonteOre(atleti, i);
        } else if (i == c_search_bycodice) {
            printf("Inserisci codice da cercare: ");
            scanf("%s", buff);
            i = (ordinamentoAttuale == byCodice) ? BinSearch(atleti, n_info.n_atleti, buff, byCodice) : LinSearch(
                    atleti, n_info.n_atleti, buff, byCodice);
            if (i == -1)
                printf("Nessun risultato");
            else
                stampaAtleta(&(atleti[i]), &categorie, stdout);
        } else if (i == c_search_bycognome) {
            printf("Inserisci cognome (anche parziale) da cercare: ");
            scanf("%s", buff);
            i = (ordinamentoAttuale == byCognome) ? BinSearch(atleti, n_info.n_atleti, buff, byCognome) : LinSearch(
                    atleti, n_info.n_atleti, buff, byCognome);
            if (i == -1)
                printf("Nessun risultato");
            else
                stampaAtleta(&(atleti[i]), &categorie, stdout);
        }
    }
    return 0;
}