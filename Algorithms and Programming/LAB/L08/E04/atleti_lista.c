#include <mem.h>
#include <ctype.h>
#include <stdlib.h>
#include "atleti.h"
#include "esercizi.h"
#include "esercizi_list.h"

typedef struct s_NodoAtleta NodoAtleta;
typedef struct s_NodoAtleta* LinkNodoAtleta;

struct s_TabAtleti{
    int n;
    LinkNodoAtleta head, tail;
};
struct s_Categoria{
    int id;
    char *nome;
};
struct s_TabCategorie{
    int n, size;
    Categoria *categorie;
};
struct s_NodoAtleta{
    Atleta val;
    LinkNodoAtleta next;
};
struct s_EsercizioPiano{
    int id_esercizio, set, rip;
};
struct s_NodoEsercizioPiano{
    EsercizioPiano val;
    LinkNodoEsercizioPiano next;
};

static TabAtleti inizializzaTabAtleti();
static Atleta p_cercaAtleta(void* cerca, TabAtleti tab_atleti, Metodo search_by);
void rimuoviEsercizioPiano(char *nome_esercizio, Atleta *, TabEsercizi);
int stampaPianoSuFile(FILE *fp, Atleta, TabEsercizi);


Data strToDate(char *string){
    Data data;
    sscanf(string, "%d/%d/%d", &data.giorno, &data.mese, &data.anno);
    data.timestamp = data.anno*10000 + data.mese*100 + data.giorno;
    return data;
}
static void strToLower(char *string){
    int i, n = strlen(string);
    for(i=0; i<n; i++)
        string[i] = (char)tolower(string[i]);
}
static void strToUpper(char *string){
    int i, n = strlen(string);
    for(i=0; i<n; i++)
        string[i] = (char)toupper(string[i]);
}
int cognomicmp(char *string_1, char *string_2){
    int i;
    strToLower(string_1);
    strToLower(string_2);
    for(i=0; string_1[i] == string_2[i]; i++);
    if(string_1[i]=='\0' || string_2[i]=='\0')
        return 0;
    return string_1[i] - string_2[i];
}

// Gestione liste
LinkNodoAtleta nuovoNodoAtleta(Atleta val, LinkNodoAtleta next){
    LinkNodoAtleta x = malloc(sizeof(*x));
    if (x==NULL)
        return NULL;
    else{
        x->val = val;
        x->next = next;
    }
    return x;
}
void inserisciAtletaCoda(Atleta atleta, TabAtleti tab_atleti){
    if(tab_atleti->head==NULL)
        tab_atleti->head = tab_atleti->tail = nuovoNodoAtleta(atleta, NULL);
    else{
        tab_atleti->tail->next = nuovoNodoAtleta(atleta, NULL);
        tab_atleti->tail = tab_atleti->tail->next;
    }
}

// Gestione atleti
static TabAtleti inizializzaTabAtleti(){
    TabAtleti tab_atleti = malloc(sizeof(*tab_atleti));
    tab_atleti->n = 0;
    tab_atleti->head = NULL;
    tab_atleti->tail = NULL;
    return tab_atleti;
}
TabAtleti leggiAtleti(char *nome_file){
    FILE *fp=NULL;
    Atleta tmp_atleta;
    TabAtleti tab_atleti = inizializzaTabAtleti();
    int i, tmp_oresettimanali;
    char tmp_codice[N_MAX+1], tmp_cognome[N_MAX+1], tmp_nome[N_MAX+1], tmp_categoria[N_MAX+1], tmp_datanascita[N_MAX+1];

    if((fp=fopen(nome_file, "r")) == NULL)exit(1);

    fscanf(fp, "%d", &(tab_atleti->n));

    for(i=0; i < tab_atleti->n; i++){
        //Codice identificativo
        fscanf(fp, "%*c%s %s %s %s %s %d", tmp_codice, tmp_cognome, tmp_nome,
            tmp_categoria, tmp_datanascita, &tmp_oresettimanali);
        tmp_atleta = newAtleta(tmp_codice, tmp_cognome, tmp_nome, tmp_categoria, tmp_datanascita, tmp_oresettimanali, NULL, NULL);
        //Puntatori a piani
        tmp_atleta.head = NULL;
        tmp_atleta.tail = NULL;
        inserisciAtletaCoda(tmp_atleta, tab_atleti);
    }
    fclose(fp);

    return tab_atleti;
}
void stampaElenco(TabAtleti tab_atleti, TabCategorie tab_categorie){
    LinkNodoAtleta x;
    char buff[N_MAX+1];
    FILE *fp = NULL;
    printf("Per stampare a video digitare \"video\", altrimenti inserire il nome del file: ");
    scanf("%s%*c", buff);
    fp = !strcmp(buff, "video") ? stdout : fopen(buff, "w");
    if(fp != stdout)fprintf(fp, "%d\n", tab_atleti->n);
    for(x = tab_atleti->head; x != NULL; x = x->next){
        stampaAtleta(x->val, fp, tab_categorie);
    }
    if(fp != stdout)
        fclose(fp);
}


void cancellaAtleta(char *codice_atleta, TabAtleti tab_atleti){
    // 1 per lista generale (next)
    // 2 per lista categoria (next_category)
    LinkNodoAtleta x, prev;
    strToUpper(codice_atleta);

    for (x=tab_atleti->head, prev=NULL; x!=NULL; prev=x, x=x->next){
        if(strcmp(x->val.codice, codice_atleta) == 0){
            if(prev == NULL)
                tab_atleti->head = x->next;
            else
                prev->next = x->next;
            if(&(tab_atleti->tail) == &x)
                tab_atleti->tail = prev;
            liberaAtleta(x);
            printf("Atleta eliminato correttamente");
            return;
        }
    }
    printf("Nessun risultato");
}
void aggiungiAtleta(TabAtleti tab_atleti){
    char tmp_codice[N_MAX+1], tmp_cognome[N_MAX+1], tmp_nome[N_MAX+1], tmp_categoria[N_MAX+1], tmp_datanascita[N_MAX+1];
    int tmp_oresettimanali;
    Atleta tmp_atleta;

    //Codice identificativo
    printf("Codice identificativo: ");
    scanf("%s", tmp_codice);
    if(!isAtletaNULL(cercaAtleta(buff, tmp_codice, byCodice))){
        printf("Codice atleta gia' presente");
        return;
    }
    strToUpper(tmp_codice);
    //Cognome
    printf("Cognome: ");
    scanf("%s", tmp_cognome);
    //Nome
    printf("Nome: ");
    scanf("%s", tmp_nome);
    //Categoria
    printf("Nome categoria: ");
    scanf("%s", tmp_categoria);
    //Data di nascita
    printf("Data di nascita (DD/MM/YYYY): ");
    scanf("%s", tmp_datanascita);
    //Monte ore
    printf("Monte ore: ");
    scanf("%d", &tmp_oresettimanali);

    tmp_atleta = newAtleta(tmp_codice, tmp_cognome, tmp_nome, tmp_categoria, tmp_datanascita, tmp_oresettimanali, NULL, NULL);
    inserisciAtletaCoda(tmp_atleta, tab_atleti);
    tab_atleti->n++;
}
static Atleta p_cercaAtleta(void* cerca, TabAtleti tab_atleti, Metodo search_by){
    LinkNodoAtleta x;
    Atleta search = inizializzaAtleta();
    switch(search_by) {
        case byCognome:
            search->cognome = strdup(cerca);
            search->nome = strdup("");
            break;
        case byCodice:
            search->codice = strdup(cerca);
            break;
        default: return NULL;
    }
    for (x=tab_atleti->head; x!=NULL; x=x->next)
        if(cmpAtleti(x->val, search, search_by, equal))
            return &(x->val);
    return NULL;
}
Atleta cercaAtleta(void* cerca, TabAtleti tab_atleti, Metodo search_by){
    Atleta atleta = inizializzaAtleta();
    Atleta p_atleta = p_cercaAtleta(cerca, tab_atleti, search_by);
    if(p_atleta == NULL)
        return AtletaNULL();
    else{
        *atleta = *p_atleta;
        return atleta;
    }
}