#ifndef _ATLETI_H
#define _ATLETI_H

#include <stdio.h>

#define CATEGORIE_INIZIALI 1
#define N_MAX 100
#define MAX_CHAR_ESERCIZI 50

typedef struct nodo_piano* link_piano;

typedef struct{
    int giorno, mese, anno, timestamp;
} Data;

typedef struct node* link;
typedef struct{
    char *codice, *nome, *cognome;
    Data data_nascita;
    int id_categoria, ore_settimanali;
    link_piano head, tail;
} Atleta;
typedef Atleta* p_Atleta;

typedef struct{
    char *nome;
    link head, tail;
} Categoria;
typedef struct{
    int id;
    Categoria *link;
} CategoriaInfo;
typedef enum {
    byCodice, byCognome
} Metodo;
typedef enum{
    less, equal, greater
} CheckType;

typedef struct{
    int n;
    link head, tail;
} TabAtleti;
typedef struct node{
    Atleta val;
    link next, next_category;
} Nodo;
typedef struct{
    link head, tail;
} LinkInfo;








n_Info leggiFile(TabAtleti*, Categoria **passed_categorie, int *sizeof_categorie);

link newNode(Atleta val, link next, link next_category);
void listInsTFast(link *hp,link *tp,Atleta val);

Data strToDate(char *string);
void strToLower(char *string);
int cognomicmp(char *string_1, char *string_2);
int check(Atleta A, Atleta B, Metodo metodo, CheckType condizione);

Atleta* listSearch(link h, void* k, Metodo search_by);

void cancellaAtleta(TabAtleti *, char *codice, Categoria* categorie);
void aggiungiAtleta(TabAtleti *, n_Info *n_info, Categoria *categorie, int *sizeof_categorie);
void aggiornaMonteOre(Atleta *atleta);
void stampaAtleta(Atleta *atleta, Categoria **categorie, FILE *fp);
void stampaElenco(link head, Categoria **categorie);

void stampaCategorie(Categoria *categorie, int n_categorie);
CategoriaInfo SearchCategory(Categoria *categorie, int n_categorie, char *cerca_nome);
CategoriaInfo newCategoria(Categoria **categorie, char *nome, int *n_categorie, int *sizeof_categorie);

#endif