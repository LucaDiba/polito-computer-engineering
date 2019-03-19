#include "esercizi_list.h"

typedef struct s_NodoEsercizioPiano NodoEsercizioPiano;
typedef struct s_NodoEsercizioPiano* LinkNodoEsercizioPiano;


LinkNodoEsercizioPiano nuovoNodoPiano(EsercizioPiano val, LinkNodoEsercizioPiano next){
    LinkNodoEsercizioPiano x = malloc(sizeof(*x));
    if (x==NULL)
        return NULL;
    else{
        x->val = val;
        x->next = next;
    }
    return x;
}
void inserisciPianoCoda(EsercizioPiano piano, Atleta *atleta){
    if(atleta->head==NULL)
        atleta->head = atleta->tail = nuovoNodoPiano(piano, NULL);
    else{
        atleta->tail->next = nuovoNodoPiano(piano, NULL);
        atleta->tail = atleta->tail->next;
    }
}

void leggiPiani(TabAtleti tab_atleti, TabEsercizi tab_esercizi){
    char buff[MAX_CHAR_ESERCIZI+1];
    EsercizioPiano tmp_piano;
    FILE *fp = NULL;
    LinkNodoAtleta x;

    for(x=tab_atleti->head; x != NULL; x = x->next){
        strcpy(buff,x->val.codice);
        strcat(buff, ".txt");
        if((fp = fopen(buff, "r")) == NULL)continue;
        while(fscanf(fp, "%s %d %d%*c", buff, &(tmp_piano.set), &(tmp_piano.rip)) != EOF){
            tmp_piano.id_esercizio = cercaEsercizio(buff, tab_esercizi).id; //si assuma che gli esercizi esistano
            inserisciPianoCoda(tmp_piano, &(x->val));
        }
        fclose(fp);
        fp = NULL;
    }
}
int stampaPianoSuFile(FILE *fp, Atleta atleta, TabEsercizi tab_esercizi){
    int i=1;
    NodoEsercizioPiano* x = NULL;

    for(x=atleta.head; x != NULL; x=x->next){
        fprintf(fp, "%s %d %d\n", getEsercizioById(x->val.id_esercizio, tab_esercizi).nome, x->val.set, x->val.rip);
    }
    return i;
}
void stampaPiano(char *codice_atleta, TabAtleti tab_atleti, TabEsercizi tab_esercizi){
    Atleta* p_atleta = p_cercaAtleta(codice, tab_atleti, byCodice);
    Atleta atleta = (p_atleta == NULL)codice_atleta AtletaNULL() : *p_atleta;
    int tmp;
    char buff[50];
    FILE *fp=NULL;

    if(isAtletaNULL(atleta)){
        printf("Nessun risultato");
        return;
    }
    if(atleta.head == NULL){
        printf("Piano allenamento vuoto");
        return;
    }

    printf("Piano allenamento:\n");
    stampaPianoSuFile(stdout, atleta, tab_esercizi);
    printf("0. salva su file\n"
                   "1. aggiungi esercizio a piano\n"
                   "2. modifica esercizio piano\n"
                   "3. rimuovi esercizio dal piano\n"
                   "4. esci\n>> ");
    scanf("%d", &tmp);
    if(tmp == 4)
        return;
    else if(tmp == 0){
        if((fp=fopen(strcat(atleta.codice, ".txt"), "w")) == NULL){
            printf("Errore nell'apertura del file");
            return;
        }
        stampaPianoSuFile(fp, atleta, tab_esercizi);
        printf("Piano stampato su file");
        fclose(fp);
        return;
    }else if(tmp == 1){
        aggiungiEsercizioPiano(codice_atleta, tab_atleti, tab_esercizi);
    }else if(tmp == 2) {
        printf("Inserisci nome esercizio da modificare: ");
        scanf("%s", buff);
        modificaEsercizioPiano(buff, atleta, tab_esercizi);
    }else if(tmp == 3){
        printf("Inserisci nome esercizio da eliminare dal piano: ");
        scanf("%s", buff);
        rimuoviEsercizioPiano(buff, p_atleta, tab_esercizi);
    }
}
void aggiungiEsercizioPiano(char *codice_atleta, TabAtleti tab_atleti, TabEsercizi tab_esercizi){
    Atleta* p_atleta = p_cercaAtleta(codice_atleta, tab_atleti, byCodice);
    EsercizioPiano piano;
    Esercizio tmp_esercizio;
    char buff[50];

    if(p_atleta == NULL){
        printf("Atleta non trovato");
        return;
    }

    printf("Inserisci nome esercizio: ");
    scanf("%s", buff);
    tmp_esercizio = cercaEsercizio(buff, tab_esercizi);
    if(isEsercizioNULL(tmp_esercizio)){
        printf("Esercizio non trovato. Aggiungerlo prima di assegnarlo al piano di un atleta");
        return;
    }
    piano.id_esercizio = tmp_esercizio.id;
    printf("Inserisci set: ");
    scanf("%d", &(piano.set));
    printf("Inserisci ripetizioni: ");
    scanf("%d", &(piano.rip));
    inserisciPianoCoda(piano, p_atleta);
    printf("Esercizio aggiutno correttamente al piano");
}
void modificaEsercizioPiano(char *nome_esercizio, Atleta atleta, TabEsercizi tab_esercizi){
    NodoEsercizioPiano* x = NULL;
    EsercizioPiano *esercizio_piano = &(atleta.head->val);
    for (x = atleta.head; x != NULL; x = x->next)
        if (strcmp(nome_esercizio, getEsercizioById(x->val.id_esercizio, tab_esercizi).nome) == 0)break;
    if (x == NULL) {
        printf("Esercizio non trovato nel piano");
        return;
    }
    printf("Set attuali: %d\nRipetizioni attuali: %d\n", esercizio_piano->set, esercizio_piano->rip);
    printf("Cambia set in: ");
    scanf("%d", &(esercizio_piano->set));
    printf("Cambia ripetizioni in: ");
    scanf("%d", &(esercizio_piano->rip));
    printf("Aggiornato\n");
}

void rimuoviEsercizioPiano(char *nome_esercizio, Atleta *atleta, TabEsercizi tab_esercizi){
    NodoEsercizioPiano *x = NULL, *x_prev = NULL;
    for(x = atleta->head; x != NULL; x_prev = x, x = x->next)
        if(strcmp(nome_esercizio, getEsercizioById(x->val.id_esercizio, tab_esercizi).nome) == 0)
            break;
    if (x == NULL) {
        printf("Esercizio non trovato nel piano");
        return;
    }
    if(x_prev == NULL){ //esercizio è il primo nel piano
        atleta->head = x->next;
    }else{
        x_prev->next = x->next;
    }
    free(x);
    printf("Rimosso");
#include "esercizi_list.h"}
typedef struct s_NodoEsercizioPiano NodoEsercizioPiano;
typedef struct s_NodoEsercizioPiano* LinkNodoEsercizioPiano;
