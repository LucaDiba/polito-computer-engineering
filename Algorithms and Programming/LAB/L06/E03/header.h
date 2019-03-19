#ifndef E03_HEADER_H
#define E03_HEADER_H

#include <malloc.h>
#include <mem.h>
#include <ctype.h>

#define CATEGORIE_INIZIALI 1
#define N_MAX 100

//Ogni nodo della lista di atleti contiene:
// - un link all'atleta successivo
// - un link all'atleta succ. della stessa categoria

typedef struct{
    int giorno, mese, anno, timestamp;
} Data;
typedef struct node* link;
typedef struct{
    char *codice, *nome, *cognome;
    Data data_nascita;
    int id_categoria, ore_settimanali;
} Atleta;
typedef Atleta Item;
typedef struct{
    struct node *byCodice, *byCognome, *byCategoria;
} AtletaOrder;
typedef struct{
    char *nome;
    link head, tail;
} Categoria;
typedef struct{
    int id;
    Categoria *link;
} CategoriaInfo;
typedef struct{
    int n_atleti, n_categorie;
} n_Info;
typedef enum {
    byCodice, byCognome
} Metodo;
typedef enum{
    less, equal, greater
} CheckType;
typedef enum{
    c_first, c_stampa_elenco, c_stampa_percategoria, c_aggiornamonteore, c_search_bycodice, c_search_bycognome, c_atleta_add, c_atleta_del, c_exit
} Comandi;

typedef struct node{
    Atleta val;
    link next, next_category;
} Nodo;
typedef struct{
    link head, tail;
} LinkInfo;

//Dichiarazioni
n_Info leggiFile(link *passed_head, link *passed_tail, Categoria **passed_categorie, int *sizeof_categorie);

link newNode(Atleta val, link next, link next_category);
void listInsTFast(link *hp,link *tp,Item val);

Data strToDate(char *string);
void strToLower(char *string);
int cognomicmp(char *string_1, char *string_2);
int check(Item A, Item B, Metodo metodo, CheckType condizione);

Item* listSearch(link h, void* k, Metodo search_by);

void cancellaAtleta(link* hp, link* tp, char *codice, Categoria* categorie);
void aggiungiAtleta(link* hp, link* tp, n_Info *n_info, Categoria *categorie, int *sizeof_categorie);
void aggiornaMonteOre(Atleta *atleta);
void stampaAtleta(Atleta *atleta, Categoria **categorie, FILE *fp);
void stampaElenco(link head, Categoria **categorie);

void stampaCategorie(Categoria *categorie, int n_categorie);
CategoriaInfo SearchCategory(Categoria *categorie, int n_categorie, char *cerca_nome);
CategoriaInfo newCategoria(Categoria **categorie, char *nome, int *n_categorie, int *sizeof_categorie);
//Fine dichiarazioni


n_Info leggiFile(link *passed_head, link *passed_tail, Categoria **passed_categorie, int *sizeof_categorie){
    n_Info n_info;
    FILE *fp=NULL;
    Atleta tmp_atleta;
    link head=NULL, tail=NULL, tmp_atleta_p;
    Categoria *categorie = malloc(CATEGORIE_INIZIALI * sizeof(Categoria));
    CategoriaInfo cat_info;
    int i, tmp_newcat;
    char buff[N_MAX+1];

    n_info.n_atleti = n_info.n_categorie = 0;
    if((fp=fopen("atleti.txt", "r")) == NULL)return n_info;

    fscanf(fp, "%d", &n_info.n_atleti);

    for(i=0; i<n_info.n_atleti; i++){
        tmp_newcat=0;
        //Codice identificativo
        fscanf(fp, "%*c%s", buff); // %*c: \n
        tmp_atleta.codice = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(tmp_atleta.codice, buff);
        //Cognome
        fscanf(fp, "%s", buff);
        tmp_atleta.cognome = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(tmp_atleta.cognome, buff);
        //Nome
        fscanf(fp, "%s", buff);
        tmp_atleta.nome = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(tmp_atleta.nome, buff);
        //Categoria
        fscanf(fp, "%s", buff);
        if((cat_info = SearchCategory(categorie, n_info.n_categorie, buff)).id == -1){
            tmp_newcat = 1;
            cat_info = newCategoria(&categorie, buff, &(n_info.n_categorie), sizeof_categorie);
        }
        tmp_atleta.id_categoria = cat_info.id;
        //Data di nascita
        fscanf(fp, "%s", buff);
        tmp_atleta.data_nascita = strToDate(buff);
        //Monte ore
        fscanf(fp, "%d", &(tmp_atleta.ore_settimanali));
        listInsTFast(&head, &tail, tmp_atleta);
        tmp_atleta_p = tail;
        //Aggiorno lista categoria


        if(tmp_newcat)
            (cat_info.link)->head = tmp_atleta_p;
        else
            (cat_info.link)->tail->next_category = tmp_atleta_p;
        (cat_info.link)->tail = tmp_atleta_p;
    }
    fclose(fp);
    *passed_head = head;
    *passed_tail = tail;
    *passed_categorie = categorie;
    return n_info;
}

link newNode(Atleta val, link next, link next_category){
    link x = malloc(sizeof(*x));
    if (x==NULL)
        return NULL;
    else{
        x->val = val;
        x->next = next;
        x->next_category = next_category;
    }
    return x;
}
void listInsTFast(link *hp,link *tp,Item val){
    if(*hp==NULL)
        *hp = *tp = newNode(val, NULL, NULL);
    else{
        (*tp)->next = newNode(val, NULL, NULL);
        *tp = (*tp)->next;
    }
}

Data strToDate(char *string){
    Data data;
    sscanf(string, "%d/%d/%d", &data.giorno, &data.mese, &data.anno);
    data.timestamp = data.anno*10000 + data.mese*100 + data.giorno;
    return data;
}
void strToLower(char *string){
    int i, n = strlen(string);
    for(i=0; i<n; i++)
        string[i] = (char)tolower(string[i]);
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
int check(Item A, Item B, Metodo metodo, CheckType condizione){
    int val, len_A, len_B;
    char *buff_A, *buff_B;
    switch (metodo){
        case byCodice:
            (B.codice)[0] = (char)toupper((B.codice)[0]);
            val = strcmp(A.codice, B.codice);
            break;
        case byCognome:
            len_A = strlen(A.nome) + strlen(A.cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_A = malloc(len_A * sizeof(char));
            strcpy(buff_A, A.cognome);
            if(strlen(A.nome)>0)
                strcat(buff_A, " ");
            strcat(buff_A, A.nome);

            len_B = strlen(B.nome) + strlen(B.cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_B = malloc(len_B * sizeof(char));
            strcpy(buff_B, B.cognome);
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

Item* listSearch(link h, void* k, Metodo search_by) {
    link x;
    Item search;
    switch(search_by) {
        case byCognome:
            search.cognome = malloc(strlen((char *) k) + 1);
            search.nome = malloc( 1 * sizeof(char) );
            strcpy(search.nome, "");
            strcpy(search.cognome, k);
            break;
        case byCodice:
            search.codice = malloc(strlen((char *) k) + 1);
            strcpy(search.codice, k);
            break;
        default: return NULL;
    }
    for (x=h; x!=NULL; x=x->next)
        if (check(x->val, search, search_by, equal))
            return &(x->val);
    return NULL;
}

void cancellaAtleta(link* hp, link* tp, char *codice, Categoria* categorie){
    // 1 per lista generale (next)
    // 2 per lista categoria (next_category)
    link x, prev;
    int eliminato_da_categoria=0;
    codice[0] = (char)toupper(codice[0]);

    for (x=*hp, prev=NULL; x!=NULL; prev=x, x=x->next){
        if(strcmp(x->val.codice, codice) == 0){
            if(prev == NULL)
                *hp = x->next;
            else
                prev->next = x->next;
            if(tp == &x)
                *tp = prev;
            if(!eliminato_da_categoria)
                categorie[x->val.id_categoria].head = x->next_category;
            free(x);
            printf("Atleta eliminato correttamente");
            return;
        }
        if(x->next_category != NULL){
            if(strcmp(x->next_category->val.codice, codice) == 0) {
                x->next_category = x->next_category->next_category;
                eliminato_da_categoria = 1;
            }
        }
    }
    printf("Nessun risultato");
}
void aggiungiAtleta(link* hp, link* tp, n_Info *n_info, Categoria *categorie, int *sizeof_categorie){
    CategoriaInfo cat_info;
    int tmp_newcat=0;
    char buff[N_MAX+1];
    Atleta tmp_atleta;
    link tmp_atleta_p;

    //Codice identificativo
    printf("Codice identificativo: ");
    scanf("%s", buff);
    if(listSearch(*hp, buff, byCodice) != NULL){
        printf("Codice atleta già presente");
        return;
    }
    tmp_atleta.codice = malloc( (strlen(buff)+1) * sizeof(char));
    buff[0] = (char)toupper(buff[0]);
    strcpy(tmp_atleta.codice, buff);
    //Cognome
    printf("Cognome: ");
    scanf("%s", buff);
    tmp_atleta.cognome = malloc( (strlen(buff)+1) * sizeof(char));
    strcpy(tmp_atleta.cognome, buff);
    //Nome
    printf("Nome: ");
    scanf("%s", buff);
    tmp_atleta.nome = malloc( (strlen(buff)+1) * sizeof(char));
    strcpy(tmp_atleta.nome, buff);
    //Categoria
    printf("Nome categoria: ");
    scanf("%s", buff);
    if((cat_info = SearchCategory(categorie, n_info->n_categorie, buff)).id == -1){
        tmp_newcat = 1;
        cat_info = newCategoria(&categorie, buff, &(n_info->n_categorie), sizeof_categorie);
    }
    tmp_atleta.id_categoria = cat_info.id;
    //Data di nascita
    printf("Data di nascita (DD/MM/YYYY): ");
    scanf("%s", buff);
    tmp_atleta.data_nascita = strToDate(buff);
    //Monte ore
    printf("Monte ore: ");
    scanf("%d", &(tmp_atleta.ore_settimanali));
    listInsTFast(hp, tp, tmp_atleta);
    tmp_atleta_p = *tp;
    //Aggiorno lista categoria
    if(tmp_newcat)
        (cat_info.link)->head = tmp_atleta_p;
    else
        (cat_info.link)->tail->next_category = tmp_atleta_p;
    (cat_info.link)->tail = tmp_atleta_p;
}
void aggiornaMonteOre(Atleta *atleta){
    int nuovo_monteore;
    printf("Inserisci nuovo monte ore: ");
    scanf("%d%*c", &nuovo_monteore);
    atleta->ore_settimanali = nuovo_monteore;
    printf("Monte ore aggiornato");
}
void stampaAtleta(Atleta *atleta, Categoria **categorie, FILE *fp){
    fprintf(fp, "[%s] %s, %s\n", atleta->codice, atleta->cognome, atleta->nome);
    fprintf(fp, "\tCategoria: %s\n", (*categorie)[atleta->id_categoria].nome);
    fprintf(fp, "\tData nasc: %02d/%02d/%04d\n", atleta->data_nascita.giorno, atleta->data_nascita.mese, atleta->data_nascita.anno);
    fprintf(fp, "\tOre setti: %d", atleta->ore_settimanali);
    fprintf(fp, "\n");
}
void stampaElenco(link head, Categoria **categorie){
    link x;
    char buff[N_MAX+1];
    FILE *fp = NULL;
    printf("Per stampare a video digitare \"video\", altrimenti inserire il nome del file: ");
    scanf("%s%*c", buff);
    fp = !strcmp(buff, "video") ? stdout : fopen(buff, "w");
    for(x = head; x != NULL; x = x->next){
        stampaAtleta(&(x->val), categorie, fp);
    }
    if(fp != stdout)
        fclose(fp);
}

void stampaCategorie(Categoria *categorie, int n_categorie){
    int i;
    link x;
    for(i=0; i<n_categorie; i++) {
        printf("\n%s\n", categorie[i].nome);
        for (x = categorie[i].head; x != NULL; x = x->next_category) {
            stampaAtleta(&(x->val), &categorie, stdout);
        }
    }
}
CategoriaInfo SearchCategory(Categoria *categorie, int n_categorie, char *cerca_nome){
    CategoriaInfo val;
    val.id = -1;
    val.link = NULL;
    int i;
    for(i=0; i<n_categorie; i++)
        if(strcmp(categorie[i].nome, cerca_nome) == 0){
            val.id = i;
            val.link = &(categorie[i]);
            break;
        }
    return val;
}
CategoriaInfo newCategoria(Categoria **categorie, char *nome, int *n_categorie, int *sizeof_categorie){
    CategoriaInfo val;
    if(*n_categorie == *sizeof_categorie){
        *categorie = realloc(*categorie, (2 * (*sizeof_categorie) * sizeof(Categoria)));
        *sizeof_categorie = (*sizeof_categorie)*2;
    }
    (*categorie)[*n_categorie].nome = malloc( (strlen(nome)+1) * sizeof(char));
    strcpy((*categorie)[*n_categorie].nome, nome);
    val.link = &((*categorie)[*n_categorie]);
    val.id = *n_categorie;

    *n_categorie = (*n_categorie)+1;
    return val;
}

#endif //E03_HEADER_H