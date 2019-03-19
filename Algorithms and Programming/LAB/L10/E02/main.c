#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define MAX_STAZIONI 100

#include "utenti.h"
#include "stazioni.h"
#include "utenti_bst.h"


int main(int argc, char **argv) {
    char tmp_id_stazione[MAX_ID_STAZIONE],
         tmp_id_carta[MAX_ID_CARTA];
    int  tmp_time, tempo_noleggio;
    FILE *fp = NULL;
    BST tab_utenti;
    tab_stazioni_t tab_stazioni;

    tab_utenti = BSTinit();
    if((fp=fopen(argv[1], "r")) == NULL){
        printf("Errore nella lettura del file %s", argv[1]);
        return 1;
    }
    tab_stazioni = leggiStazioni(fp);
    fclose(fp);

    while(1){
        printf("Pronto a leggere");
        scanf("%s %s %d", tmp_id_stazione, tmp_id_carta, &tmp_time);
        if(strcmp(tmp_id_stazione, "0") == 0)
            return 0;

        cercaOAggiungi(tmp_id_carta, tab_utenti);

        if(noleggioAttivo(tmp_id_carta, tab_utenti)){
            if(getNumeroPostiLiberi(tmp_id_stazione, tab_stazioni) > 0){
                tempo_noleggio = chiudiNoleggio(tmp_id_stazione, tmp_id_carta, tmp_time, tab_utenti, tab_stazioni);
                printf("Noleggio terminato correttamente. E` durato %d minuti\n", tempo_noleggio);
            }else{ // non sono presenti posti liberi
                printf("Spiacenti, al momento in questa stazione non sono presenti posti liberi\n");
            }
        }else{ // nessun noleggio attivo - inizio nuovo noleggio
            if(getNumeroBici(tmp_id_stazione, tab_stazioni) > 0){
                avviaNoleggio(tmp_id_stazione, tmp_id_carta, tmp_time, tab_utenti, tab_stazioni);
                printf("Noleggio avviato correttamente\n");
            }else{ // non sono presenti bici
                printf("Spiacenti, al momento in questa stazione non sono presenti bici\n");
            }
        }
    }
}


