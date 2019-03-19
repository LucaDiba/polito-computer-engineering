#ifndef _ATLETI_H
#define _ATLETI_H

/*
Inizializzare le categorie tramite inizializzaCategorie()
prima di eseguire leggiAtleti
*/

#include <stdio.h>
#include <stdlib.h>
#include "atleta.h"
#include "esercizi.h"
#include "atleti_lista.h"

#define CATEGORIE_INIZIALI 1
#define N_MAX 100
#define MAX_CHAR_ESERCIZI 50

#ifndef t_string
    #define t_string
    typedef char* string;
#endif
#ifndef t_data
    #define t_data
    typedef struct{
	    int giorno, mese, anno, timestamp;
	} Data;
#endif

typedef struct s_Categoria Categoria;
typedef struct s_TabCategorie *TabCategorie;

// Gestione dati NULL
Categoria CategoriaNULL();
int isCategoriaNULL(Categoria);

// Gestione atleti
void aggiornaMonteOre(Atleta, TabAtleti);

/* Generazione, modifica e distruzione atleta */
void aggiungiAtleta(TabAtleti);
void cancellaAtleta(Atleta, TabAtleti);

Atleta cercaAtleta(void* cerca, TabAtleti, Metodo search_by);
void stampaAtleta(Atleta, FILE *fp);


// Gestione categorie
TabCategorie inizializzaTabCategorie();
Categoria cercaCategoria(string nome_categoria, TabCategorie);
Categoria cercaCategoriaById(int id, TabCategorie);
Categoria nuovaCategoria(string nome_categoria, TabCategorie);
void stampaAtletiPerCategoria(TabAtleti, TabCategorie);

#endif