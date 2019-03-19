#ifndef _ATLETI_H
#define _ATLETI_H

#include <stdio.h>
#include "esercizi.h"
#define CATEGORIE_INIZIALI 1
#define N_MAX 100
#define MAX_CHAR_ESERCIZI 50

typedef struct s_NodoEsercizioPiano* LinkNodoEsercizioPiano;

typedef struct{
    int giorno, mese, anno, timestamp;
} Data;

typedef struct s_NodoAtleta* LinkNodoAtleta;
typedef struct{
    char *codice, *nome, *cognome;
    Data data_nascita;
    int ore_settimanali, id_categoria;
    LinkNodoEsercizioPiano head, tail;
} Atleta;
typedef struct s_TabAtleti{
    int n;
    LinkNodoAtleta head, tail;
} *TabAtleti;
typedef struct{
    struct node *byCodice, *byCognome, *byCategoria;
} AtletaOrder;

typedef struct{
    int id;
    char *nome;
} Categoria;
typedef struct {
    int n, size;
    Categoria *categorie;
} *TabCategorie;

typedef enum {
    byCodice, byCognome
} Metodo;
typedef enum{
    less, equal, greater
} CheckType;

typedef struct s_NodoAtleta{
    Atleta val;
    LinkNodoAtleta next;
} NodoAtleta;


typedef struct s_Piano{
    int id_esercizio, set, rip;
} EsercizioPiano;
typedef struct s_NodoEsercizioPiano{
    EsercizioPiano val;
    LinkNodoEsercizioPiano next;
} NodoEsercizioPiano;

// Gestione strutture NULL
Atleta AtletaNULL();
int isAtletaNULL(Atleta atleta);
Categoria CategoriaNULL();
int isCategoriaNULL(Categoria categoria);

// Gestione atleti
//TabAtleti inizializzaTabAtleti();
int checkAtleti(Atleta A, Atleta B, Metodo, CheckType condizione);
TabAtleti leggiAtleti(char *nome_file, TabCategorie);
void cancellaAtleta(char *codice_atleta, TabAtleti);
void aggiungiAtleta(TabAtleti, TabCategorie);
Atleta* p_cercaAtleta(void* cerca, TabAtleti, Metodo search_by);
Atleta cercaAtleta(void* cerca, TabAtleti, Metodo search_by);
void stampaAtleta(Atleta, FILE *fp, TabCategorie);
void stampaElenco(TabAtleti, TabCategorie);
void aggiornaMonteOre(Atleta, TabAtleti);

// Gestione categorie
TabCategorie inizializzaTabCategorie();
Categoria cercaCategoria(char *nome_categoria, TabCategorie);
Categoria cercaCategoriaById(int id, TabCategorie);
Categoria nuovaCategoria(char *nome_categoria, TabCategorie);
void stampaAtletiPerCategoria(TabAtleti, TabCategorie);

// Gestione piani esercizi
void leggiPiani(TabAtleti, TabEsercizi);
int stampaPianoSuFile(FILE *fp, Atleta, TabEsercizi);
void stampaPiano(char *codice, TabAtleti, TabEsercizi);
void aggiungiEsercizioPiano(char *codice_atleta, TabAtleti, TabEsercizi);
void modificaEsercizioPiano(char *nome_esercizio, Atleta, TabEsercizi);
void rimuoviEsercizioPiano(char *nome_esercizio, Atleta *, TabEsercizi);

#endif