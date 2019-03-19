#include <mem.h>
#include <malloc.h>
#include "stazioni.h"

/* STRUTTURE DATI */
struct stazione_t_s{
    char    id_stazione[MAX_ID_STAZIONE];
    int     n_stazione,
            num_bici, num_posti;
};
struct tab_stazioni_t_s{
    stazione_t *stazioni;
    int n;
};

/* PROTOTIPI FUNZIONI STATICHE */
static stazione_t p_cercaStazione(char*, tab_stazioni_t);

/* FUNZIONI */
stazione_t stazioneNULL(){
    return nuovaStazione(-1, "", 0, 0);
}
int isStazioneNULL(stazione_t stazione){
    if(stazione->n_stazione == -1)
        return 1;
    else
        return 0;
}
stazione_t nuovaStazione(int n_stazione, char *id_stazione, int num_bici, int num_posti){
    stazione_t stazione = malloc(sizeof(*stazione));

    stazione->n_stazione = n_stazione;
    strcpy(stazione->id_stazione, id_stazione);
    stazione->num_bici  = num_bici;
    stazione->num_posti = num_posti;

    return stazione;
}

tab_stazioni_t leggiStazioni(FILE* fp){
    int i, n,
        tmp_num_bici, tmp_num_posti;
    char tmp_id_stazione[MAX_ID_STAZIONE];
    tab_stazioni_t tab_stazioni = malloc(sizeof(*tab_stazioni));

    fscanf(fp, "%d", &n);
    tab_stazioni->stazioni = malloc(n * sizeof(stazione_t));
    for (i=0; i<n; i++){
        fscanf(fp, " %s %d %d", tmp_id_stazione, &tmp_num_bici, &tmp_num_posti);
        tab_stazioni->stazioni[i] = nuovaStazione(i, tmp_id_stazione, tmp_num_bici, tmp_num_posti);
    }

    tab_stazioni->n = n;
    return tab_stazioni;
}

int getNumeroPosti(char *id_stazione, tab_stazioni_t tab_stazioni){
    return p_cercaStazione(id_stazione, tab_stazioni)->num_posti;
}
int getNumeroBici(char *id_stazione, tab_stazioni_t tab_stazioni){
    return p_cercaStazione(id_stazione, tab_stazioni)->num_bici;
}
int getNumeroPostiLiberi(char *id_stazione, tab_stazioni_t tab_stazioni){
    stazione_t stazione = p_cercaStazione(id_stazione, tab_stazioni);
    return stazione->num_posti - stazione->num_bici;
}

static stazione_t p_cercaStazione(char* id_stazione, tab_stazioni_t tab_stazioni){
    int i;

    for(i=0; i<tab_stazioni->n; i++){
        if(strcmp(id_stazione, tab_stazioni->stazioni[i]->id_stazione) == 0)
            return tab_stazioni->stazioni[i];
    }
    return NULL;
}

stazione_t cercaStazione(char* id_stazione, tab_stazioni_t tab_stazioni){
    stazione_t p_stazione, stazione = malloc(sizeof(*stazione));
    p_stazione = p_cercaStazione(id_stazione, tab_stazioni);
    if(p_stazione == NULL)
        stazione = stazioneNULL();
    else{
        strcpy(stazione->id_stazione, p_stazione->id_stazione);
        stazione->n_stazione = p_stazione->n_stazione;
        stazione->num_bici   = p_stazione->num_bici;
        stazione->num_posti  = p_stazione->num_posti;
    }
    return stazione;
}

void aggiungiBici(char *id_stazione, tab_stazioni_t tab_stazioni){
    stazione_t stazione = p_cercaStazione(id_stazione, tab_stazioni);
    stazione->num_bici++;
}
void rimuoviBici (char *id_stazione, tab_stazioni_t tab_stazioni){
    stazione_t stazione = p_cercaStazione(id_stazione, tab_stazioni);
    stazione->num_bici--;
}

int getNStazione(char *id_stazione, tab_stazioni_t tab_stazioni){
    stazione_t stazione = cercaStazione(id_stazione, tab_stazioni);
    if(isStazioneNULL(stazione))
        return -1;
    else
        return stazione->n_stazione;
}