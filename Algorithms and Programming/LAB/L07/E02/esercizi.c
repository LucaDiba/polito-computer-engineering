#include "atleti.h"

static link_piano newNodePiano(Piano, link_piano);
static void listInsTFastPiano(Piano, Atleta *);

/*
link_piano newNodePiano(Piano val, link_piano next){
    link_piano x = malloc(sizeof(*x));
    if (x==NULL)
        return NULL;
    else{
        x->val = val;
        x->next = next;
    }
    return x;
}
void listInsTFastPiano(Piano val, Atleta *atleta){
    if(atleta->head==NULL)
        atleta->head = atleta->tail = newNodePiano(val, NULL);
    else{
        atleta->tail->next = newNodePiano(val, NULL);
        atleta->tail = atleta->tail->next;
    }
}
*/
TabEsercizi leggiEsercizi(char *nome_file){
    int i;
    char buff[MAX_CHAR_ESERCIZI+1];
    FILE *fp = NULL;
    Esercizio *esercizi = NULL;


    if((fp=fopen(nome_file, "r")) == NULL)return -1;
    fscanf(fp, "%d", &(tab_esercizi->n));
    esercizi = malloc(tab_esercizi->n * sizeof(Esercizio));
    for(i=0; i<tab_esercizi->n; i++){
        //Nome esercizio
        fscanf(fp, "%*c%s", buff);
        esercizi[i].nome = strdup(buff);
        //Categoria
        fscanf(fp, "%s", buff);
        esercizi[i].categoria = strdup(buff);
        //Tipologia
        fscanf(fp, "%s", buff);
        esercizi[i].tipo = strdup(buff);
    }
    tab_esercizi->vettEsercizi = esercizi;
    fclose(fp);
    return 1;
}
void stampaEsercizi(TabEsercizi tabEsercizi){
    int i;
    Esercizio *esercizi = tabEsercizi->vettEsercizi;
    for(i=0; i < tabEsercizi.n; i++){
        printf("%s\n"
                       "\tCategoria: %s\n"
                       "\tTipo: %s\n", esercizi[i].nome, esercizi[i].tipo, esercizi[i].categoria);
    }
}

Esercizio* getEsercizioPointerFromName(char *cerca, TabEsercizi tab_esercizi){
    int i;
    Esercizio *esercizi = tab_esercizi->vettEsercizi;
    for(i=0; i<tab_esercizi.n; i++){
        if(strcmp(esercizi[i].nome, cerca) == 0)
            return &(esercizi[i]);
    }
    return NULL;
}
/*
void leggiPiani(TabAtleti tab_atleti, TabEsercizi tab_esercizi){
    int i, tmp_set, tmp_rip;
    char buff[MAX_CHAR_ESERCIZI+1];
    Piano tmp_piano;
    FILE *fp = NULL;
    link x;

    for(x=tab_atleti.head; x != NULL; x = x->next){
        strcpy(buff,x->val.codice);
        strcat(buff, ".txt");
        if((fp = fopen(buff, "r")) == NULL)continue;
        while(fscanf(fp, "%s %d %d%*c", buff, &tmp_piano.set, &tmp_piano.rip) != EOF){
            tmp_piano.esercizio = getEsercizioPointerFromName(buff, tab_esercizi);
            listInsTFastPiano(tmp_piano, &(x->val));
        }

        fclose(fp);
        fp = NULL;
    }
}

void stampaPiano(TabAtleti tab_atleti, char *codice){
    Atleta* atleta = listSearch(tab_atleti.head, codice, byCognome);
    NodoPiano* x = NULL;
    int i,tmp;
    FILE *fp=NULL;

    if(atleta == NULL){
        printf("Nessun risultato");
        return;
    }
    if(atleta->head == NULL){
    	printf("Piano allenamento vuoto");
    	return;
    }

    printf("Piano allenamento:\n");
    i = stampaPianoSuFile(stdout, atleta);
    printf("Inserire:\n"
    	"- 0 (zero) per salvare su file\n"
    	"- numero esercizio da modificare\n"
    	"- qualsiasi altro numero per uscire\n>> ");
    scanf("%d", &tmp);
    if(tmp < 0 || tmp >= i)
        return;
    if(tmp == 0){
    	if((fp=fopen(strcat(atleta->codice, ".txt"), "w")) == NULL){
    		printf("Errore nell'apertura del file");
    		return;
    	}
    	stampaPianoSuFile(fp, atleta);
    	fclose(fp);
    }

    for(x=atleta->head, i=1; x != NULL; x=x->next, i++)
        if(i == tmp)break;
    if(x==NULL)
        return;
    modificaEsercizioPiano(&(x->val));
}

int stampaPianoSuFile(FILE *fp, Atleta *atleta){
	int i=1;
	NodoPiano* x = NULL;

    for(x=atleta->head, i=1; x != NULL; x=x->next, i++){
    	if(fp == stdout)
    		/* non ha molto senso usare la fprintf sapendo che fp == stdout
    		   ma stampando a video penso sia meglio "formattare" l'output
    		*/
        	fprintf(fp, "[%d] - %2d x %2d\t%s\n", i, x->val.set, x->val.rip, x->val.esercizio->nome);
        else
        	fprintf(fp, "%s %d %d\n", x->val.esercizio->nome, x->val.set, x->val.rip);
    }
    return i;
}

void modificaEsercizioPiano(Piano *piano){
    printf("Set attuali: %d\nRipetizioni attuali: %d\n", piano->set, piano->rip);
    printf("Cambia set in: ");
    scanf("%d", &(piano->set));
    printf("Cambia ripetizioni in: ");
    scanf("%d", &(piano->rip));
    printf("Aggiornato\n");
}