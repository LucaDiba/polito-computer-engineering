#include "esercizio.h"

struct s_Esercizio{
    int id;
    string nome, categoria, tipo;
}* Esercizio;

Esercizio EsercizioNULL(){
	return NULL;
}
int isEsercizioNULL(Esercizio esercizio){
    return (esercizio == NULL) ? 1 : 0;
}