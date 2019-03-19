#ifndef _ITEM_H
#define _ITEM_H

#define MAX_CHAR_PARTECIPANTE 50
typedef struct s_partecipante* Item;

Item ITEMinit();
Item ITEMscan();
Item ITEMFileScan(FILE* fp);

int ITEMless(Item, Item);
int ITEMgreater(Item, Item);
void ITEMshow(Item, FILE*);
int ITEMnamecmp(char *, Item);

int ITEMgetPunteggio(Item);
char* ITEMgetNome(Item);
void ITEMcambiaPunteggio(Item, int nuovo_punteggio);

#endif //_ITEM_H