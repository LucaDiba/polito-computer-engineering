#ifndef E02_UTENTI_H
#define E02_UTENTI_H

#include "stazioni.h"

#ifndef MAX_STAZIONI
#define MAX_STAZIONI 100
#endif // ndef MAX_STAZIONI

#define MAX_ID_CARTA 10

typedef struct binarysearchtree *tab_utenti_t;
typedef struct utente_t_s *utente_t;

utente_t utenteNULL();
int      isUtenteNULL(utente_t);
int      cmpUtenteLess(utente_t, utente_t); // ritorna (utente_1 < utente_2)
char*    getCodiceUtente(utente_t);

void     nuovoUtente(char *id_carta, tab_utenti_t);
utente_t cercaUtente(char *id_carta, tab_utenti_t);
int      noleggioAttivo(char *id_carta, tab_utenti_t);
utente_t cercaOAggiungi(char *id_carta, tab_utenti_t);

/* Controllare che i noleggi siano o meno attivi prima di richiamare
 * le seguenti funzioni
 */
int  chiudiNoleggio(char* id_stazione, char* id_carta, int time, tab_utenti_t tab_utenti, tab_stazioni_t); // Ritorna la durata del noleggio attuale in minuti
void avviaNoleggio (char* id_stazione, char* id_carta, int time, tab_utenti_t tab_utenti, tab_stazioni_t);

utente_t	BSTsearch      (tab_utenti_t, char*);
void    	BSTinsert_leafI(tab_utenti_t, utente_t);

#endif //E02_UTENTI_H