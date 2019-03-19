#define ARROW_L 1
#define ARROW_R 0

typedef struct{
	int *seq, n;
} *TabSequenza;

TabSequenza leggiFrecce(char* nome_file);
int daCambiarePerValidare(TabSequenza);
int cambia(int da_cambiare, TabSequenza tab_sequenza);
int validaSoluzione(int* sol, TabSequenza tab_sequenza);