#include <mem.h>
#include <malloc.h>
#include "utenti.h"

/* STRUTTURE DATI */
struct utente_t_s{
    char id_carta[MAX_ID_CARTA];
    int  utilizzi_stazioni[MAX_STAZIONI],// vettore sovrallocato per evitare di allocarlo dinamicamente per ogni utente
         inizio_noleggio;                // time inizio ultimo noleggio, oppure -1 se non e` attivo alcun noleggio
};

/* PROTOTIPI FUNZIONI STATICHE */
static utente_t p_cercaUtente(char* id_carta, tab_utenti_t); // puntatore ad utente

/* FUNZIONI */
void nuovoUtente(char* id_carta, tab_utenti_t bst){
    utente_t utente = malloc(sizeof(*utente));
    int i;

    strcpy(utente->id_carta, id_carta);
    for(i=0; i<MAX_STAZIONI; i++)
        utente->utilizzi_stazioni[i] = 0;
    utente->inizio_noleggio = -1;

    BSTinsert_leafI(bst, utente);
}

utente_t utenteNULL(){
    utente_t utente = malloc(sizeof(*utente));
    strcpy(utente->id_carta, "");

    return utente;
}

int isUtenteNULL(utente_t utente){
    if(strcmp(utente->id_carta, "") == 0)
        return 1;
    else
        return 0;
}

int cmpUtenteLess(utente_t val_1, utente_t val_2){
    return strcmp(val_1->id_carta, val_2->id_carta)<0;
}

char* getCodiceUtente(utente_t utente){
    return utente->id_carta;
}

int noleggioAttivo(char* id_carta, tab_utenti_t bst){
    utente_t utente = p_cercaUtente(id_carta, bst);

    if(utente->inizio_noleggio == -1)
        return 0;
    else
        return 1;
}

static utente_t p_cercaUtente(char* id_carta, tab_utenti_t bst){
    return BSTsearch(bst, id_carta);
}

utente_t cercaOAggiungi(char *id_carta, tab_utenti_t tab_utenti){
    if(isUtenteNULL(p_cercaUtente(id_carta, tab_utenti)))
        nuovoUtente(id_carta, tab_utenti);

    return p_cercaUtente(id_carta, tab_utenti);
}

int chiudiNoleggio(char* id_stazione, char* id_carta, int time, tab_utenti_t tab_utenti, tab_stazioni_t tab_stazioni){
    int time_noleggio;
    utente_t p_utente = p_cercaUtente(id_carta, tab_utenti);
    int n_stazione = getNStazione(id_stazione, tab_stazioni);

    aggiungiBici(id_stazione, tab_stazioni);
    p_utente->utilizzi_stazioni[n_stazione]++;
    time_noleggio = time - p_utente->inizio_noleggio;
    p_utente->inizio_noleggio = -1;

    return time_noleggio;
}
void avviaNoleggio (char* id_stazione, char* id_carta, int time, tab_utenti_t tab_utenti, tab_stazioni_t tab_stazioni){
    utente_t p_utente = p_cercaUtente(id_carta, tab_utenti);
    int n_stazione = getNStazione(id_stazione, tab_stazioni);

    rimuoviBici(id_stazione, tab_stazioni);
    p_utente->utilizzi_stazioni[n_stazione]++;
    p_utente->inizio_noleggio = time;
}