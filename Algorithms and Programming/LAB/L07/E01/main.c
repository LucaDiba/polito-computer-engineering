#include "header.h"

int main(int argc, char **argv) {
	Citta *citta = NULL;
    Distanza *distanze = NULL;
    Soluzione soluzione;
    int n_citta, n_ato;
    
    if(argc != 3)return -1;
    n_ato = atoi(argv[2]);
    if((n_citta = leggiFile(argv[1], &citta)) == -1)return -1;
    generaDistanzeTraCitta(citta, n_citta, &distanze);
    soluzione = calcolaCittaOttimali(citta, n_citta, distanze, n_ato);
    stampaSoluzione(citta, n_ato, soluzione);
    return 0;
}