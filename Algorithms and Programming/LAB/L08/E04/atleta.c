#include "atleta.h"

static typedef enum{
    less, equal, greater
} CheckType;

struct s_Atleta{
    string codice, nome, cognome, categoria;
    Data data_nascita;
    int ore_settimanali;
    LinkNodoEsercizioPiano head, tail;
};

// Dichiatazione funzioni statiche
static Atleta* p_cercaAtleta(void* cerca, TabAtleti, Metodo search_by);
static int checkAtleti(Atleta A, Atleta B, Metodo, CheckType condizione);
// Fine dichiarazione


Atleta AtletaNULL(){
    return NULL;
}
int isAtletaNULL(Atleta atleta){
    return (atleta == NULL) ? 1 : 0;
}

Atleta inizializzaAtleta(){
    Atleta atleta = malloc(sizeof *atleta);
    return atleta;
}

Atleta newAtletaMonteOre(Atleta atleta, int nuovo_monteore){
    atleta->ore_settimanali = nuovo_monteore;
    return atleta;
}

Atleta newAtleta(char* codice, char* cognome, char* nome, char* categoria, char* data_nascita, int ore_settimanali, void* head, void* tail){
    Atleta atleta = inizializzaAtleta();
    
    atleta->codice = strdup(codice);
    atleta->cognome = strdup(cognome);
    atleta->nome = strdup(nome);
    atleta->categoria = strdup(categoria);
    atleta->data_nascita = strToDate(data_nascita);
    atleta->ore_settimanali = ore_settimanali;
    atleta->head = head;
    atleta->tail = tail;
    return atleta;
}

void stampaAtleta(Atleta atleta, FILE *fp){
    fprintf(fp, "%s %s %s %s ", atleta->codice, atleta->cognome, atleta->nome, atleta->categoria);
    fprintf(fp, "%02d/%02d/%04d ", atleta->data_nascita.giorno, atleta->data_nascita.mese, atleta->data_nascita.anno);
    fprintf(fp, "%d", atleta->ore_settimanali);
    fprintf(fp, "\n");
}


int cmpAtleti(Atleta A, Atleta B, Metodo metodo, CheckType condizione){
    int val, len_A, len_B;
    char *buff_A, *buff_B;
    switch (metodo){
        case byCodice:
            (B->codice)[0] = (char)toupper((B->codice)[0]);
            val = strcmp(A->codice, B->codice);
            break;
        case byCognome:
            len_A = strlen(A->nome) + strlen(A->cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_A = strdup(A->cognome);
            if(strlen(A->nome)>0)
                strcat(buff_A, " ");
            strcat(buff_A, A->nome);

            len_B = strlen(B->nome) + strlen(B->cognome) + 2; // +2 perché +1 ' ' e +1 '\0'
            buff_B = strdup(B->cognome);
            if(strlen(B->nome)>0)
                strcat(buff_B, " ");
            strcat(buff_B, B->nome);

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

void liberaAtleta(Atleta atleta){
    if(atleta == NULL)
        return;
    free(atleta->codice);
    free(atleta->cognome);
    free(atleta->nome);
    free(atleta->categoria);
    liberaPiano(atleta->head);
    free(atleta);
}