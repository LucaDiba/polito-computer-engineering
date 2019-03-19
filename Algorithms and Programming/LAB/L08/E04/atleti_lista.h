#ifndef _ATLETI_LIST_H
#define _ATLETI_LIST_H

#include "atleta.h"
#include "atleti.h"

typedef struct s_TabAtleti *TabAtleti;

TabAtleti leggiAtleti(char* nome_file);
void stampaElenco(TabAtleti, TabCategorie);

#endif //_ATLETI_LIST_H
