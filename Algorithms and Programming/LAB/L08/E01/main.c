#include "koala.h"

int main(){
	TabKoala tab_koala;
	TabFamiglie tab_famiglie;
	Vincoli vincoli;
	int m=2;

	tab_koala = acquisisciKoala("habitat.txt");
	tab_famiglie = acquisisciFamiglie("famiglie.txt", "nemici.txt", tab_koala);

	printf("Solo vincolo famiglie:\n");
	vincoli.habitat = 0;
	vincoli.famiglie = 1;
	//determinaAllocazione(m, tab_koala, tab_famiglie, vincoli);

	printf("Entrambi i vincoli:\n");
	vincoli.habitat = 1;
	vincoli.famiglie = 1;
	determinaAllocazione(m, tab_koala, tab_famiglie, vincoli);
}