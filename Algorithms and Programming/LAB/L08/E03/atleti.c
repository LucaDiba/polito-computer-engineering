#include <mem.h>
#include <ctype.h>
#include <stdlib.h>
#include "atleti.h"
#include "esercizi.h"

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

// Gestione strutture NULL
Atleta AtletaNULL(){
    Atleta atleta;
    atleta.codice = NULL;
    return atleta;
}
int isAtletaNULL(Atleta atleta){
    return (atleta.codice == NULL) ? 1 : 0;
}
Categoria CategoriaNULL(){
    Categoria categoria;
    categoria.id = -1;
    return categoria;
}
int isCategoriaNULL(Categoria categoria){
    return (categoria.id == -1) ? 1 : 0;
}

// Gestione atleti
TabAtleti inizializzaTabAtleti(){
    TabAtleti tab_atleti = malloc(sizeof(*tab_atleti));
    tab_atleti->n = 0;
    tab_atleti->head = NULL;
    tab_atleti->tail = NULL;
    return tab_atleti;
}
int checkAtleti(Atleta A, Atleta B, Metodo metodo, CheckType condizione){
    int val, len_A, len_B;
    char *buff_A, *buff_B;
    switch (metodo){
        case byCodice:
            (B.codice)[0] = (char)toupper((B.codice)[0]);
            val = strcmp(A.codice, B.codice);
            break;
        case byCognome:
            len_A = strlen(A.nome) + strlen(A.cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_A = strdup(A.cognome);
            if(strlen(A.nome)>0)
                strcat(buff_A, " ");
            strcat(buff_A, A.nome);

            len_B = strlen(B.nome) + strlen(B.cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_B = strdup(B.cognome);
            if(strlen(B.nome)>0)
                strcat(buff_B, " ");
            strcat(buff_B, B.nome);

            val = cognomicmp(buff_A, buff_B);
            free(buff_A);
            free(buff_B);
            break;
        default:
            return -1;
    }
    if(condizione == equal) return val==0;
    if(condizione == less) return val<0;
    if(condizione == greater) return val>0;
}
TabAtleti leggiAtleti(char *nome_file, TabCategorie tab_categorie){
    FILE *fp=NULL;
    Atleta tmp_atleta;
    Categoria tmp_categoria;
    TabAtleti tab_atleti = inizializzaTabAtleti();
    int i;
    char buff[N_MAX+1];

    if((fp=fopen(nome_file, "r")) == NULL)exit(1);

    fscanf(fp, "%d", &(tab_atleti->n));

    for(i=0; i < tab_atleti->n; i++){
        //Codice identificativo
        fscanf(fp, "%*c%s", buff); // %*c: \n
        tmp_atleta.codice = strdup(buff);
        //Cognome
        fscanf(fp, "%s", buff);
        tmp_atleta.cognome = strdup(buff);
        //Nome
        fscanf(fp, "%s", buff);
        tmp_atleta.nome = strdup(buff);
        //Categoria
        fscanf(fp, "%s", buff);
        tmp_categoria = cercaCategoria(buff, tab_categorie);
        if(isCategoriaNULL(tmp_categoria))
            tmp_atleta.id_categoria = nuovaCategoria(buff, tab_categorie).id;
        else
            tmp_atleta.id_categoria = tmp_categoria.id;
        //Data di nascita
        fscanf(fp, "%s", buff);
        tmp_atleta.data_nascita = strToDate(buff);
        //Monte ore
        fscanf(fp, "%d", &(tmp_atleta.ore_settimanali));
        //Puntatori a piani
        tmp_atleta.head = NULL;
        tmp_atleta.tail = NULL;
        inserisciAtletaCoda(tmp_atleta, tab_atleti);
    }
    fclose(fp);

    return tab_atleti;
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
            free(x);
            printf("Atleta eliminato correttamente");
            return;
        }
    }
    printf("Nessun risultato");
}
void aggiungiAtleta(TabAtleti tab_atleti, TabCategorie tab_categorie){
    char buff[N_MAX+1];
    Atleta tmp_atleta;
    Categoria tmp_categoria;

    //Codice identificativo
    printf("Codice identificativo: ");
    scanf("%s", buff);
    if(!isAtletaNULL(cercaAtleta(buff, tab_atleti, byCodice))){
        printf("Codice atleta gia' presente");
        return;
    }
    strToUpper(buff);
    tmp_atleta.codice = strdup(buff);
    //Cognome
    printf("Cognome: ");
    scanf("%s", buff);
    tmp_atleta.cognome = strdup(buff);
    //Nome
    printf("Nome: ");
    scanf("%s", buff);
    tmp_atleta.nome = strdup(buff);
    //Categoria
    printf("Nome categoria: ");
    scanf("%s", buff);
    tmp_categoria = cercaCategoria(buff, tab_categorie);
    if(isCategoriaNULL(tmp_categoria))
        tmp_atleta.id_categoria = nuovaCategoria(buff, tab_categorie).id;
    else
        tmp_atleta.id_categoria = tmp_categoria.id;
    //Data di nascita
    printf("Data di nascita (DD/MM/YYYY): ");
    scanf("%s", buff);
    tmp_atleta.data_nascita = strToDate(buff);
    //Monte ore
    printf("Monte ore: ");
    scanf("%d", &(tmp_atleta.ore_settimanali));
    //Puntatori a piani
    tmp_atleta.head = NULL;
    tmp_atleta.tail = NULL;
    inserisciAtletaCoda(tmp_atleta, tab_atleti);
    tab_atleti->n++;
}
Atleta* p_cercaAtleta(void* cerca, TabAtleti tab_atleti, Metodo search_by){
    LinkNodoAtleta x;
    Atleta search;
    switch(search_by) {
        case byCognome:
            search.cognome = strdup(cerca);
            search.nome = strdup("");
            break;
        case byCodice:
            search.codice = strdup(cerca);
            break;
        default: return NULL;
    }
    for (x=tab_atleti->head; x!=NULL; x=x->next)
        if(checkAtleti(x->val, search, search_by, equal))
            return &(x->val);
    return NULL;
}
Atleta cercaAtleta(void* cerca, TabAtleti tab_atleti, Metodo search_by){
    Atleta* p_atleta = p_cercaAtleta(cerca, tab_atleti, search_by);
    if(p_atleta == NULL)
        return AtletaNULL();
    else
        return *p_atleta;
}
void stampaAtleta(Atleta atleta, FILE *fp, TabCategorie tab_categorie){
    if(fp == stdout){
        fprintf(fp, "[%s] %s, %s\n", atleta.codice, atleta.cognome, atleta.nome);
        fprintf(fp, "\tCategoria: %s\n", cercaCategoriaById(atleta.id_categoria, tab_categorie).nome);
        fprintf(fp, "\tData nasc: %02d/%02d/%04d\n", atleta.data_nascita.giorno, atleta.data_nascita.mese, atleta.data_nascita.anno);
        fprintf(fp, "\tOre setti: %d", atleta.ore_settimanali);
        fprintf(fp, "\n");
    }else{
        fprintf(fp, "%s %s %s ", atleta.codice, atleta.cognome, atleta.nome);
        fprintf(fp, "%s ", cercaCategoriaById(atleta.id_categoria, tab_categorie).nome);
        fprintf(fp, "%02d/%02d/%04d ", atleta.data_nascita.giorno, atleta.data_nascita.mese, atleta.data_nascita.anno);
        fprintf(fp, "%d", atleta.ore_settimanali);
        fprintf(fp, "\n");
    }
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
void aggiornaMonteOre(Atleta atleta, TabAtleti tab_atleti){
    int nuovo_monteore;
    Atleta* p_atleta = p_cercaAtleta(atleta.codice, tab_atleti, byCodice);
    if(p_atleta == NULL)
        return;

    printf("Inserisci nuovo monte ore: ");
    scanf("%d%*c", &nuovo_monteore);
    p_atleta->ore_settimanali = nuovo_monteore;
    printf("Monte ore aggiornato");
}

// Gestione categorie
TabCategorie inizializzaTabCategorie(){
    TabCategorie tab_categorie = malloc(sizeof(*tab_categorie));
    tab_categorie->n = 0;
    tab_categorie->size = CATEGORIE_INIZIALI;
    tab_categorie->categorie = malloc(CATEGORIE_INIZIALI * sizeof(Categoria));
    return tab_categorie;
}
Categoria cercaCategoria(char *nome_categoria, TabCategorie tab_categorie){
    Categoria categoria = CategoriaNULL();
    int i;
    strToUpper(nome_categoria);
    for(i=0; i<tab_categorie->n; i++)
        if(strcmp((tab_categorie->categorie)[i].nome, nome_categoria) == 0){
            categoria = (tab_categorie->categorie)[i];
            break;
        }
    return categoria;
}
Categoria cercaCategoriaById(int id, TabCategorie tab_categorie){
    Categoria categoria = CategoriaNULL();
    if(id>=0 && id<tab_categorie->n){
        categoria = tab_categorie->categorie[id];
    }
    return categoria;
}

Categoria nuovaCategoria(char *nome_categoria, TabCategorie tab_categorie){
    int n = tab_categorie->n, size = tab_categorie->size;
    if(n == size){
        tab_categorie->categorie = realloc(tab_categorie->categorie, (2 * size * sizeof(Categoria)));
        size *= 2;
    }
    (tab_categorie->categorie)[n].nome = strdup(nome_categoria);
    (tab_categorie->categorie)[n].id = n;
    n++;

    tab_categorie->n = n;
    tab_categorie->size = size;

    return (tab_categorie->categorie)[n-1];
}
void stampaAtletiPerCategoria(TabAtleti tab_atleti, TabCategorie tab_categorie){
    int i, n_categorie = tab_categorie->n;
    Categoria *categorie = tab_categorie->categorie;
    LinkNodoAtleta x = NULL;

    for(i=0; i<n_categorie; i++) {
        printf("\n%s\n", categorie[i].nome);
        for(x=tab_atleti->head; x!=NULL; x=x->next){
            if(x->val.id_categoria == i){
                stampaAtleta(x->val, stdout, tab_categorie);
            }
        }
    }
}

// Gestione piani esercizi
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
void stampaPiano(char *codice, TabAtleti tab_atleti, TabEsercizi tab_esercizi){
    Atleta* p_atleta = p_cercaAtleta(codice, tab_atleti, byCodice);
    Atleta atleta = (p_atleta == NULL) ? AtletaNULL() : *p_atleta;
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
        aggiungiEsercizioPiano(codice, tab_atleti, tab_esercizi);
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
}