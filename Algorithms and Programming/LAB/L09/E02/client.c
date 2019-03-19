#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include "PQ.h"

enum{
    c_0, c_stampa, c_aggiungi, c_elimina, c_sfida, c_carica, c_salva, c_exit
};

int main() {
    PQ pq; FILE *fp = NULL;
    int selezione, tmp, punteggio_diff, punteggio_a, punteggio_b, flag_a_del, flag_b_del;
    char buff[50+1];
    Item item_1, item_2;

    srand((unsigned int)time(NULL));

    printf("Numero massimo partecipanti: ");
    scanf("%d", &tmp);
    pq = PQinit(tmp);

    while(1) {
        printf("1. stampa classifica\n"
        "2. aggiungi partecipante\n"
        "3. elimina partecipante\n"
        "4. sfida tra 2 partecipanti con punteggio minore\n"
        "5. carica dati da file\n"
        "6. salva dati su file\n");
        scanf("%d", &selezione);
        if(selezione == c_exit)
            break;

        if(selezione == c_stampa){
            PQStampaRanking(pq, stdout);
        }else if(selezione == c_aggiungi){
            PQadd(pq);
        }else if(selezione == c_elimina){
            printf("Inserisci nome atleta da eliminare: ");
            scanf("%s", buff);
            PQdeleteItem(pq, buff);
        }else if(selezione == c_sfida){
            if(PQsize(pq) < 2){
                printf("Sono necessari almeno 2 partecipanti per organizzare una sfida!\n");
                continue;
            }
            item_1 = PQextractMin(pq);
            item_2 = PQextractMin(pq);

            printf("La sfida avverra` tra \"%s\" e \"%s\"\n", ITEMgetNome(item_1), ITEMgetNome(item_2));

            punteggio_a = ITEMgetPunteggio(item_1);
            punteggio_b = ITEMgetPunteggio(item_2);
            flag_a_del = 0;
            flag_b_del = 0;
            if(rand()%2 == 0){ //vincitore: a
                printf("Vincitore: %s!\n", ITEMgetNome(item_1));
                punteggio_diff = (int)ceil((float)punteggio_b * 25 / 100);
                punteggio_a += punteggio_diff;
                punteggio_b -= punteggio_diff;
                if(punteggio_b == 0){
                    printf("%s e` stato eliminato dal torneo\n", ITEMgetNome(item_2));
                    flag_b_del = 1;
                }
            }else{ //vincitore: b
                printf("Vincitore: %s!\n", ITEMgetNome(item_2));
                punteggio_diff = (int)ceil((float)punteggio_a * 25 / 100);
                punteggio_b += punteggio_diff;
                punteggio_a -= punteggio_diff;
                if(punteggio_a == 0){
                    printf("%s e` stato eliminato dal torneo\n", ITEMgetNome(item_1));
                    flag_a_del = 1;
                }
            }
            ITEMcambiaPunteggio(item_1, punteggio_a);
            ITEMcambiaPunteggio(item_2, punteggio_b);

            if(!flag_a_del)
                PQinsert(pq, item_1);
            if(!flag_b_del)
                PQinsert(pq, item_2);

            PQStampaRanking(pq, stdout);
        }else if(selezione == c_carica){
            printf("Nome file: ");
            scanf("%s", buff);
            if((fp=fopen(buff, "r")) == NULL){
                printf("Errore nell'apertura del file in lettura\n");
                continue;
            }
            PQLeggi(pq, fp);
            fclose(fp);
            printf("Dati caricati correttamente\n");
        }else if(selezione == c_salva){
            printf("Nome file: ");
            scanf("%s", buff);
            if((fp=fopen(buff, "w")) == NULL){
                printf("Errore nell'apertura del file in scrittura\n");
                continue;
            }
            PQStampa(pq, fp);
            fclose(fp);
        }
    }
    return 0;
}