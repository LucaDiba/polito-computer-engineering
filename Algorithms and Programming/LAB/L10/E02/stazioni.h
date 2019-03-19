#ifndef E02_STAZIONI_H
#define E02_STAZIONI_H

#include <stdio.h>

#define MAX_ID_STAZIONE 10

typedef struct stazione_t_s *stazione_t;
typedef struct tab_stazioni_t_s *tab_stazioni_t;

stazione_t     nuovaStazione (int n_stazione, char *id_stazione, int num_posti, int num_bici);
stazione_t     stazioneNULL  (void);
int            isStazioneNULL(stazione_t);
int            getNStazione  (char *id_stazione, tab_stazioni_t);
tab_stazioni_t leggiStazioni (FILE*);
/* Anche se avendo due dati e` possibile recuperare il terzo, si preferisce
 * calcolarlo in una funzione per evitare di effettuare una ricerca della stazione
 * piu` volte. E` tuttavia irrilevante poiché la complessita` non cambia
 * e il numero di stazioni e` trascurabile rispetto al nummero di utenti
 */
int        getNumeroPosti      (char *id_stazione, tab_stazioni_t);
int        getNumeroBici       (char *id_stazione, tab_stazioni_t);
int        getNumeroPostiLiberi(char *id_stazione, tab_stazioni_t);

void       aggiungiBici(char *id_stazione, tab_stazioni_t);
void       rimuoviBici (char *id_stazione, tab_stazioni_t);


#endif //E02_STAZIONI_H