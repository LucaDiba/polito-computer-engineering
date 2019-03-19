#include <stdio.h>
#include <assert.h>
#include "esercizi.h"
#include "atleti.h"

typedef enum{
    c_first, c_stampa_elenco, c_stampa_percategoria, c_stampa_esercizi, c_cerca_stampa_esercizio, c_aggiornamonteore, c_search_bycodice, c_search_bycognome, c_atleta_add, c_atleta_del, c_exit
} Comandi;

int main(){
    TabCategorie tab_categorie = inizializzaTabCategorie();
    TabAtleti tab_atleti;
    Atleta tmp_atleta;
    Esercizio tmp_esercizio;
    TabEsercizi tab_esercizi;
    int i;
    char buff[N_MAX+1];
    
    tab_atleti = leggiAtleti("atleti.txt", tab_categorie);
    tab_esercizi = leggiEsercizi("esercizi.txt");
    leggiPiani(tab_atleti, tab_esercizi);

    while(1) {
        fseek(stdin,0,SEEK_END);
        i=0;
        printf("\nEFFETTUA UNA SCELTA:\n"
                       "%d. stampa anagrafica\n"
                       "%d. stampa atleti per categoria\n"
                       "%d. stampa esercizi disponibili\n"
                       "%d. cerca e stampa esercizio\n"
                       "%d. aggiornamento monte ore settimanali\n"
                       "%d. ricerca atleta per codice\n"
                       "%d. ricerca atleta per cognome\n"
                       "%d. aggiungi atleta\n"
                       "%d. cancella atleta\n"
                       "%d. esci\n"
                       "Codice selezione: ", c_stampa_elenco, c_stampa_percategoria, c_stampa_esercizi, c_cerca_stampa_esercizio, c_aggiornamonteore,
               c_search_bycodice, c_search_bycognome, c_atleta_add, c_atleta_del, c_exit);
        scanf("%d%*c", &i);
        if (i == c_exit)
            break;
        if (i <= c_first || i > c_exit) {
            printf("Scelta non valida");
            continue;
        }
        if (i == c_stampa_elenco) {
            stampaElenco(tab_atleti, tab_categorie);
        } else if (i == c_stampa_percategoria){
            stampaAtletiPerCategoria(tab_atleti, tab_categorie);
        } else if (i == c_stampa_esercizi){
            stampaElencoEsercizi(tab_esercizi);
        } else if (i == c_cerca_stampa_esercizio){
            printf("Inserisci nome esercizio: ");
            scanf("%s", buff);
            tmp_esercizio = cercaEsercizio(buff, tab_esercizi);
            if(isEsercizioNULL(tmp_esercizio))
                printf("Nessun esercizio trovato");
            else
                stampaEsercizio(tmp_esercizio);
        } else if (i == c_aggiornamonteore) {
            printf("Inserisci codice atleta da aggiornare: ");
            scanf("%s", buff);
            tmp_atleta = cercaAtleta(buff, tab_atleti, byCodice);
            if (isAtletaNULL(tmp_atleta))
                printf("Nessun risultato");
            else
                aggiornaMonteOre(tmp_atleta, tab_atleti);
        } else if (i == c_search_bycodice) {
            printf("Inserisci codice atleta da cercare: ");
            scanf("%s", buff);
            tmp_atleta = cercaAtleta(buff, tab_atleti, byCodice);
            if(isAtletaNULL(tmp_atleta))
                printf("Nessun risultato");
            else{
                stampaAtleta(tmp_atleta, stdout, tab_categorie);
                stampaPiano(tmp_atleta.codice, tab_atleti, tab_esercizi);
            }
        } else if (i == c_search_bycognome) {
            printf("Inserisci cognome atleta da cercare: ");
            scanf("%s", buff);
            tmp_atleta = cercaAtleta(buff, tab_atleti, byCognome);
            if (isAtletaNULL(tmp_atleta))
                printf("Nessun risultato");
            else {
                stampaAtleta(tmp_atleta, stdout, tab_categorie);
                stampaPiano(tmp_atleta.codice, tab_atleti, tab_esercizi);
            }
        } else if (i == c_atleta_add) {
            aggiungiAtleta(tab_atleti, tab_categorie);
        } else if (i == c_atleta_del) {
            printf("Inserisci codice atleta da eliminare: ");
            scanf("%s", buff);
            cancellaAtleta(buff, tab_atleti);
        }
    }
    return 0;
}