#include "header.h"

int main() {
    Prodotto *prodotti = NULL;
    int n_prodotti, n_min, prezzo_min;
    char buff[8+1];

    n_prodotti = leggiFile("prodotti.txt", &prodotti);
    do{
        printf("Inserisci numero minimo prodotti: ");
        scanf("%d", &n_min);
    }while(n_min < 0);
    do{
        printf("Inserisci budget massimo nel formato (n.cc): ");
        scanf("%s", buff);
    }while((prezzo_min = stringToCentesimi(buff)) != -1);
    powerset(prodotti, n_prodotti, n_min, prezzo_min);

    return 0;
}