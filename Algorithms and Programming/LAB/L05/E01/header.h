#ifndef E01NN_HEADER_H
#define E01NN_HEADER_H

#include <malloc.h>
#include <mem.h>
#include <math.h>
#include <ctype.h>

#define CATEGORIE_INIZIALI 1
#define N_MAX 100

typedef struct{
    int giorno, mese, anno, timestamp;
} Data;
typedef struct{
    char *nome;
} Categoria;
typedef struct{
    char *codice, *nome, *cognome;
    Data data_nascita;
    int id_categoria, ore_settimanali;
} Atleta;
typedef Atleta Item;
typedef struct{
    int n_atleti, n_categorie;
} n_Info;
typedef enum {
    byCodice, byCognome, byDataNascita, byCategoria, byAcquisizione
} Metodo;
typedef enum{
    less, equal, greater
} CheckType;
typedef enum{
    c_first, c_stampa_elenco, c_order_bydatanascita, c_order_bycodice, c_order_bycognome, c_stampa_percategoria, c_aggiornamonteore, c_search_bycodice, c_search_bycognome, c_exit
} Comandi;

int SearchCategory(Categoria *categorie, int n_categorie, char *cerca_nome);
int newCategoria(Categoria **categorie, char *nome, int *n_categorie, int *sizeof_categorie);
void strToLower(char *string);
int cognomicmp(char *string_1, char *string_2);
int check(Item A, Item B, Categoria *categorie, Metodo order_metodo, CheckType condizione);

void MergeSortAtleti(Item *A, int n_atleti, Categoria *categorie, Metodo order_metodo);
void MergeSortR(Item *A, Item *B, Categoria *categorie, int l, int r, Metodo order_metodo);
void Merge(Item *A, Item *B, Categoria *categorie, int l, int q, int r, Metodo order_metodo);

int BinSearchR(Item v[], Categoria *categorie, int l, int r, Item k, Metodo checkMetodo);
int BinSearch(Item *atleti, int n_atleti, char *search, Metodo searchMetodo);
int LinSearch(Item *atleti, int n_atleti, char *search, Metodo searchMetodo);

Data strToDate(char *string);
n_Info leggiFile(Atleta **passed_atleti, Categoria **passed_categorie);
void stampaAtleta(Atleta *atleta, Categoria **categorie, FILE *fp);
void stampaElenco(Atleta *atleti, int n_atleti, Categoria **categorie);
void aggiornaMonteOre(Atleta *atleti, int id_atleta);


int SearchCategory(Categoria *categorie, int n_categorie, char *cerca_nome){
    int i;
    for(i=0; i<n_categorie; i++)
        if(strcmp(categorie[i].nome, cerca_nome) == 0)
            return i;
    return -1;
}
int newCategoria(Categoria **categorie, char *nome, int *n_categorie, int *sizeof_categorie){
    if(*n_categorie == *sizeof_categorie){
        *categorie = realloc(*categorie, (2 * (*sizeof_categorie) * sizeof(Categoria)));
        *sizeof_categorie = (*sizeof_categorie)*2;
    }
    (*categorie)[*n_categorie].nome = malloc( (strlen(nome)+1) * sizeof(char));
    strcpy((*categorie)[*n_categorie].nome, nome);
    *n_categorie = (*n_categorie)+1;
    return (*n_categorie)-1;
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
int check(Item A, Item B, Categoria *categorie, Metodo order_metodo, CheckType condizione){
    int val, len_A, len_B;
    char *buff_A, *buff_B;
    switch (order_metodo){
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
        case byDataNascita:
            val = A.data_nascita.timestamp - B.data_nascita.timestamp;
            break;
        case byCategoria:
            val = strcmp(categorie[A.id_categoria].nome, categorie[B.id_categoria].nome);
            break;
        default:
            return -1;
    }
    if(condizione == equal) return val==0;
    if(condizione == less) return val<0;
    if(condizione == greater) return val>0;
}

void MergeSortAtleti(Item *A, int n_atleti, Categoria *categorie, Metodo order_metodo){
    int l=0, r=n_atleti-1;
    Item *B = (Item *)malloc(n_atleti*sizeof(Item));
    MergeSortR(A, B, categorie, l, r, order_metodo);
}
void MergeSortR(Item *A, Item *B, Categoria *categorie, int l, int r, Metodo order_metodo){
    int q = (l + r)/2;
    if (r <= l)
        return;
    MergeSortR(A, B, categorie, l, q, order_metodo);
    MergeSortR(A, B, categorie, q+1, r, order_metodo);
    Merge(A, B, categorie, l, q, r, order_metodo);
}
void Merge(Item *A, Item *B, Categoria *categorie, int l, int q, int r, Metodo order_metodo){
    int i, j, k;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if ( !check(A[i], A[j], categorie, order_metodo, greater) )
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}

int BinSearchR(Item v[], Categoria *categorie, int l, int r, Item k, Metodo checkMetodo){
    int m;
    if(r == l)
        if(check(v[l], k, categorie, checkMetodo, equal))
            return l;
        else
            return -1;
    m = (l+r) / 2;
    if(!check(v[m], k, categorie, checkMetodo, less))
        return(BinSearchR(v, categorie, l, m, k, checkMetodo));
    else
        return(BinSearchR(v, categorie, m+1, r, k, checkMetodo));
}
int BinSearch(Item *atleti, int n_atleti, char *search, Metodo searchMetodo){
    Atleta cerca;
    Categoria *categorie = NULL;
    int l=0, r=n_atleti-1;

    if(searchMetodo == byCodice){
        cerca.codice = malloc( strlen(search) * sizeof(char) );
        strcpy(cerca.codice, search);
    }else if(searchMetodo == byCognome){
        cerca.cognome = malloc( strlen(search) * sizeof(char) );
        strcpy(cerca.cognome, search);
        cerca.nome = malloc( 1 * sizeof(char) );
        strcpy(cerca.nome, "");
    }else return -1;

    return BinSearchR(atleti, categorie, l, r, cerca, searchMetodo);
}
int LinSearch(Item *atleti, int n_atleti, char *search, Metodo searchMetodo){
    Atleta cerca;
    Categoria *categorie = NULL;
    int i;

    if(searchMetodo == byCodice){
        cerca.codice = malloc( strlen(search) * sizeof(char) );
        strcpy(cerca.codice, search);
    }else if(searchMetodo == byCognome){
        cerca.cognome = malloc( strlen(search) * sizeof(char) );
        strcpy(cerca.cognome, search);
        cerca.nome = malloc( 1 * sizeof(char) );
        strcpy(cerca.nome, "");
    }else return -1;

    for(i=0; i<n_atleti; i++){
        if(check(atleti[i], cerca, categorie, searchMetodo, equal))
            return i;
    }
    return -1;
}

Data strToDate(char *string){
    Data data;
    sscanf(string, "%d/%d/%d", &data.giorno, &data.mese, &data.anno);
    data.timestamp = data.anno*10000 + data.mese*100 + data.giorno;
    return data;
}
n_Info leggiFile(Atleta **passed_atleti, Categoria **passed_categorie){
    n_Info n_info;
    FILE *fp=NULL;
    Atleta *atleti = NULL;
    Categoria *categorie = malloc(CATEGORIE_INIZIALI * sizeof(Categoria));

    int i, id_categoria, sizeof_categorie = CATEGORIE_INIZIALI;
    char buff[N_MAX+1];

    n_info.n_atleti = n_info.n_categorie = 0;
    if((fp=fopen("atleti.txt", "r")) == NULL)return n_info;

    fscanf(fp, "%d", &n_info.n_atleti);
    atleti = malloc(n_info.n_atleti * sizeof(Atleta));

    for(i=0; i<n_info.n_atleti; i++){
        //Codice identificativo
        fscanf(fp, "%*c%s", buff); // %*c: \n
        atleti[i].codice = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(atleti[i].codice, buff);
        //Cognome
        fscanf(fp, "%s", buff);
        atleti[i].cognome = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(atleti[i].cognome, buff);
        //Nome
        fscanf(fp, "%s", buff);
        atleti[i].nome = malloc( (strlen(buff)+1) * sizeof(char));
        strcpy(atleti[i].nome, buff);
        //Categoria
        fscanf(fp, "%s", buff);
        id_categoria = SearchCategory(categorie, n_info.n_categorie, buff);
        id_categoria = (id_categoria == -1) ? newCategoria(&categorie, buff, &(n_info.n_categorie), &sizeof_categorie) : id_categoria;
        atleti[i].id_categoria = id_categoria;
        //Data di nascita
        fscanf(fp, "%s", buff);
        atleti[i].data_nascita = strToDate(buff);
        //Monte ore
        fscanf(fp, "%d", &(atleti[i].ore_settimanali));
    }
    fclose(fp);
    *passed_atleti = atleti;
    *passed_categorie = categorie;
    return n_info;
}
void stampaAtleta(Atleta *atleta, Categoria **categorie, FILE *fp){
    fprintf(fp, "[%s] %s, %s\n", atleta->codice, atleta->cognome, atleta->nome);
    fprintf(fp, "\tCategoria: %s\n", (*categorie)[atleta->id_categoria].nome);
    fprintf(fp, "\tData nasc: %02d/%02d/%04d\n", atleta->data_nascita.giorno, atleta->data_nascita.mese, atleta->data_nascita.anno);
    fprintf(fp, "\tOre setti: %d", atleta->ore_settimanali);
    fprintf(fp, "\n");
}
void stampaElenco(Atleta *atleti, int n_atleti, Categoria **categorie){
    int i;
    char buff[N_MAX+1];
    FILE *fp = NULL;
    printf("Per stampare a video digitare \"video\", altrimenti inserire il nome del file: ");
    scanf("%s%*c", buff);
    fp = !strcmp(buff, "video") ? stdout : fopen(buff, "w");
    for(i=0; i<n_atleti; i++)
        stampaAtleta(&(atleti[i]), categorie, fp);
}
void aggiornaMonteOre(Atleta *atleti, int id_atleta){
    int nuovo_monteore;
    printf("Inserisci nuovo monte ore: ");
    scanf("%d%*c", &nuovo_monteore);
    atleti[id_atleta].ore_settimanali = nuovo_monteore;
    printf("Monte ore aggiornato");
}
void stampaCategorie(Atleta *passed_atleti, Categoria *categorie, n_Info n_info){
    int i, id_categoria_attuale=-1;
    Atleta *atleti = malloc(sizeof(Atleta) * n_info.n_atleti);
    for(i=0; i<n_info.n_atleti; i++)
        atleti[i] = passed_atleti[i];
    MergeSortAtleti(atleti, n_info.n_atleti, categorie, byCategoria);
    for(i=0; i<n_info.n_atleti; i++) {
        if(atleti[i].id_categoria != id_categoria_attuale){
            id_categoria_attuale = atleti[i].id_categoria;
            printf(">> Categoria: %s\n", categorie[id_categoria_attuale].nome);
        }
        stampaAtleta(&(atleti[i]), &categorie, stdout);
    }
}

#endif //E01NN_HEADER_H