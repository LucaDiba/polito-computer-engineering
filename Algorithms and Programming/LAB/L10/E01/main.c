#include <stdio.h>
#include <malloc.h>

//#define DEBUG 1


/* Parametri */
#define MAX_R 50
#define MAX_C 50

#define RIGHE   10
#define COLONNE 10

#define BUDGET 40

/* Strutture dati */
typedef enum {
    nemico, alleato
} tipo_target;
typedef enum {
    t_risorsa, t_target
} tipo_elemento;
typedef struct {
    int r, c;
} coordinate_t;

// Risorse
typedef struct {
    int         id_risorsa,
                raggio_azione,
                attacco, difesa,
                costo;
} risorsa_t;
typedef struct {
    risorsa_t    risorsa;
    coordinate_t coordinate;
} risorse_coordinate_t;
typedef struct {
    risorsa_t*  risorse;
    int         n_risorse;
} *tab_risorse_t;

// Target
typedef struct {
    tipo_target tipo;
    int         r, c,               // riga, colonna
                valore_riferimento;
} target_t;
typedef struct {
    target_t*   target;
    int         n_target;
} *tab_target_t;

// Mappa
typedef struct {
    tipo_elemento tipo;
    int         piena,
                id_elemento,    // id_target o id_risorsa
                effetto_attacco,
                effetto_difesa; // effetto cumulato dalle risorse nei paraggi
} cella_t;
typedef struct {
    cella_t mappa[MAX_R][MAX_C];
    int n_righe, n_colonne;
} *mappa_t;

/* Prototipi */
tab_risorse_t   leggiRisorse(FILE *);
mappa_t         inizializzaMappa(int n_righe, int n_colonne);
tab_target_t    leggiTarget(FILE *fp_alleati, FILE *fp_nemici, mappa_t);
void            incrementaEffettiMappa(mappa_t, int riga, int colonna, int add_atk, int add_def, int raggio);
void            risolviMappa(mappa_t, tab_target_t, tab_risorse_t, int budget);
void            stampaMappa (mappa_t, tab_target_t);
void            stampaMappaEffetto(mappa_t);
void            liberaMappa  (mappa_t);
void            liberaRisorse(tab_risorse_t);
void            liberaTarget (tab_target_t);


/* Funzione compare per quick sort */
int cmpfunc(const void * a, const void * b) {
    int uno = (*(risorsa_t*)a).attacco + (*(risorsa_t*)a).difesa;
    int due = (*(risorsa_t*)b).attacco + (*(risorsa_t*)b).difesa;
    return (uno-due);
}

int main() {
    tab_risorse_t tab_risorse;
    tab_target_t tab_target;
    mappa_t mappa = inizializzaMappa(RIGHE, COLONNE);

    FILE *fp_1 = NULL, *fp_2 = NULL;

    fp_1 = fopen("risorse.txt", "r");
    tab_risorse = leggiRisorse(fp_1);
    fclose(fp_1);

    fp_1 = fopen("alleati.txt", "r");
    fp_2 = fopen("nemici.txt", "r");
    tab_target = leggiTarget(fp_1, fp_2, mappa);
    fclose(fp_1);
    fclose(fp_2);
#ifdef DEBUG
    stampaMappa(mappa, tab_target);
#endif
    risolviMappa(mappa, tab_target, tab_risorse, BUDGET);

    liberaMappa  (mappa);
    liberaRisorse(tab_risorse);
    liberaTarget (tab_target);

    return 0;
}


void stampaMappa(mappa_t mappa, tab_target_t tab_target){
    int i, j;
    for(i=0; i<mappa->n_righe; i++){
        if(i==0){
            for(j=-1; j<mappa->n_colonne; j++)
                printf("|%3d", j);
            printf("\n|  0");
        }else{
            printf("|%3d", i);
        }
        for(j=0; j<mappa->n_colonne; j++){
            printf("|");
            if(mappa->mappa[i][j].piena){
                if(mappa->mappa[i][j].tipo == t_target){
                    if(tab_target->target[mappa->mappa[i][j].id_elemento].tipo == alleato)
                        printf("A");
                    else
                        printf("N");
                }
                printf("%2d", tab_target->target[mappa->mappa[i][j].id_elemento].valore_riferimento);
            }else
                printf("   ");
        }
        printf("\n");
    }
}
void stampaMappaEffetto(mappa_t mappa){
    int i, j;
    for(i=0; i<mappa->n_righe; i++){
        if(i==0){
            for(j=-1; j<mappa->n_colonne; j++)
                printf("|%7d", j);
            printf("\n|      0");
        }else{
            printf("|%7d", i);
        }
        for(j=0; j<mappa->n_colonne; j++){
            printf("|");
            if(mappa->mappa[i][j].piena){
                printf("%3d-%3d", mappa->mappa[i][j].effetto_attacco, mappa->mappa[i][j].effetto_difesa);
            }else
                printf("       ");
        }
        printf("\n");
    }
}

tab_risorse_t leggiRisorse(FILE * fp){
    tab_risorse_t tab_risorse = malloc(sizeof(*tab_risorse));
    risorsa_t tmp_risorsa;
    int i, n;

    fscanf(fp, "%d", &n);
    tab_risorse->risorse = malloc(n * sizeof(*(tab_risorse->risorse)));

    for(i=0; i<n; i++){

        fscanf(fp, " %d %d %d %d",
               &tmp_risorsa.raggio_azione,
               &tmp_risorsa.attacco,
               &tmp_risorsa.difesa,
               &tmp_risorsa.costo);
        tmp_risorsa.id_risorsa = i;
        tab_risorse->risorse[i] = tmp_risorsa;
    }
    tab_risorse->n_risorse = n;

    return tab_risorse;
}

void liberaRisorse(tab_risorse_t tab_risorse){
    free(tab_risorse);
}

void svuotaCella(int riga, int colonna, mappa_t mappa){
    mappa->mappa[riga][colonna].piena           = 0;
    mappa->mappa[riga][colonna].effetto_attacco = 0;
    mappa->mappa[riga][colonna].effetto_difesa  = 0;
}

mappa_t inizializzaMappa(int n_righe, int n_colonne){
    mappa_t  mappa = malloc(sizeof(*mappa));
    int i, j;

    // Setto tutte le celle "vuote" e senza effetto
    for(i=0; i<n_righe; i++)
        for(j=0; j<n_colonne; j++)
            svuotaCella(i, j, mappa);

    mappa->n_righe   = n_righe;
    mappa->n_colonne = n_colonne;

    return mappa;
}

void liberaMappa(mappa_t mappa){
    free(mappa);
}

void impostaTarget(target_t target, int id_target, mappa_t mappa){
    if(mappa->mappa[target.r][target.c].piena++){
        printf("Errore nel posizionamento di un target: cella <%d, %d> gia` occupata (%d)", target.r, target.c, --mappa->mappa[target.r][target.c].piena);
        exit(0);
    }
#ifdef DEBUG
    printf("Target posizionato in <%d, %d>\n", target.r, target.c);
#endif
    mappa->mappa[target.r][target.c].id_elemento = id_target;
    mappa->mappa[target.r][target.c].tipo = t_target;
}

tab_target_t leggiTarget(FILE *fp_alleati, FILE *fp_nemici, mappa_t mappa){
    tab_target_t tab_target = malloc(sizeof(*tab_target));
    target_t tmp_target;
    int i, n_alleati, n_nemici;

    fscanf(fp_alleati, "%d", &n_alleati);
    fscanf(fp_nemici,  "%d", &n_nemici);

    tab_target->target = malloc((n_alleati+n_nemici) * sizeof(*(tab_target->target)));

#ifdef DEBUG
    printf("Lettura file alleati\n");
#endif
    for(i=0; i<n_alleati; i++){
        fscanf(fp_alleati, " %d %d %d", &tmp_target.r, &tmp_target.c, &tmp_target.valore_riferimento);
        tmp_target.tipo = alleato;

        impostaTarget(tmp_target, i, mappa);
        tab_target->target[i] = tmp_target;
    }
#ifdef DEBUG
    printf("Lettura file nemici\n");
#endif
    for(   ; i<n_alleati+n_nemici; i++){
        fscanf(fp_nemici, " %d %d %d", &tmp_target.r, &tmp_target.c, &tmp_target.valore_riferimento);
        tmp_target.tipo = nemico;

        impostaTarget(tmp_target, i, mappa);
        tab_target->target[i] = tmp_target;
    }
    tab_target->n_target = n_alleati+n_nemici;
    return tab_target;
}

void liberaTarget(tab_target_t tab_target){
    free(tab_target->target);
    free(tab_target);
}

void incrementaEffettiMappa(mappa_t mappa, int riga, int colonna, int add_atk, int add_def, int raggio){
    int i, j, j_start;
    int reach_i = riga    + raggio;
    int reach_j = colonna + raggio;

    // Vado r righe su e r colonne a sx (considerando i bordi), dove r e` il raggio d'azione
    for(i=riga;    i > riga    - raggio && i>0; i--);
    for(j=colonna; j > colonna - raggio && j>0; j--);
    j_start = j;

    for( ; i!=reach_i && i<mappa->n_righe; i++){
        for(j=j_start; j!=reach_j && j<mappa->n_colonne; j++){
            mappa->mappa[i][j].effetto_attacco += add_atk;
            mappa->mappa[i][j].effetto_difesa  += add_def;
        }
    }
}

int ciSonoTargetNelRaggio(coordinate_t coordinate, int raggio, mappa_t mappa){
    int i, j, j_start;
    int reach_i = coordinate.r + raggio;
    int reach_j = coordinate.c + raggio;

    // Vado r righe su e r colonne a sx (considerando i bordi), dove r e` il raggio d'azione
    for(i=coordinate.r; i > coordinate.r - raggio && i>0; i--);
    for(j=coordinate.c; j > coordinate.c - raggio && j>0; j--);
    j_start = j;

    for( ; i!=reach_i && i<mappa->n_righe; i++){
        for(j=j_start; j!=reach_j && j<mappa->n_colonne; j++){
            if(mappa->mappa[i][j].tipo == t_target)
                return 1;
        }
    }
    return 0;
}

int impostaRisorsa(risorsa_t risorsa, coordinate_t coordinate, mappa_t mappa){
    if(mappa->mappa[coordinate.r][coordinate.c].piena || !ciSonoTargetNelRaggio(coordinate, risorsa.raggio_azione, mappa))
        return 0;
    mappa->mappa[coordinate.r][coordinate.c].piena = 1;

    mappa->mappa[coordinate.r][coordinate.c].tipo        = t_risorsa;
    mappa->mappa[coordinate.r][coordinate.c].id_elemento = risorsa.id_risorsa;

    incrementaEffettiMappa(mappa, coordinate.r, coordinate.c, risorsa.attacco, risorsa.difesa, risorsa.raggio_azione);

    return 1;
}

void eliminaRisorsa(risorsa_t risorsa, coordinate_t coordinate, mappa_t mappa){
    cella_t cella = mappa->mappa[coordinate.r][coordinate.c];

    if(cella.tipo == t_risorsa){
        mappa->mappa[coordinate.r][coordinate.c].piena = 0;
        incrementaEffettiMappa(mappa, coordinate.r, coordinate.c, -risorsa.attacco, -risorsa.difesa, risorsa.raggio_azione);
    }else{
        printf("Chiamata non consentita: non e` presente una risorsa in <%d, %d>", coordinate.r, coordinate.c);
        exit(1);
    }
}

/* VERIFICA MAPPA
 * Controlla se la disposizione delle risorse permette di vincere la partita
 */
int verificaMappa(mappa_t mappa, tab_risorse_t tab_risorse, tab_target_t tab_target, risorse_coordinate_t *sol, int n, int k){
    int i, flag = 0, i_end = k;
    cella_t   tmp_cella;
    target_t  tmp_target;

    for(i=0; i < k && flag == 0; i++)
        if (impostaRisorsa(sol[i].risorsa, sol[i].coordinate, mappa) == 0) {
            flag  = 1;
            i_end = i;
        }

    for(i=0; i<tab_target->n_target && flag == 0; i++){
        tmp_target = tab_target->target[i];
        tmp_cella  = mappa->mappa[tmp_target.r][tmp_target.c];

        if(tmp_target.tipo == alleato){
            if(tmp_target.valore_riferimento > tmp_cella.effetto_difesa)
                flag = 1;
        }else if(tmp_target.tipo == nemico){
            if(tmp_target.valore_riferimento > tmp_cella.effetto_attacco)
                flag = 1;
        }
    }

    if(!flag){ // Mappa risolta
        int costo = 0;
        printf("Sono state posizionate le seguenti risorse:\n");
        for(i=0; i<k; i++){
            costo += sol[i].risorsa.costo;
            printf("%2d) risorsa con ATK %d e DEF %d in <%2d, %2d> (costo: %d)\n", i+1, sol[i].risorsa.attacco, sol[i].risorsa.attacco, sol[i].coordinate.r, sol[i].coordinate.c, sol[i].risorsa.costo);
        }
        printf("Costo totale: %d\n", costo);
#ifdef DEBUG
        printf("Mappa con effetti per ogni cella:\n");
        stampaMappaEffetto(mappa);
#endif
    }

    for(i=0; i < i_end; i++)
        eliminaRisorsa(sol[i].risorsa, sol[i].coordinate, mappa);

    return !flag;
}

/* PIAZZAMENTO RISORSE SU MAPPA
 * Piazza le risorse date sulla mappa in tutti i modi possibili
 * Modello: disposizioni semplici - disporre N*R celle in n_elementi risorse selezionate
 */

int piazzaRisorseSuMappaR(mappa_t mappa, tab_risorse_t tab_risorse, tab_target_t tab_target,
                          int pos, coordinate_t *val, risorse_coordinate_t *sol, int *mark, int n, int k){
    int i;
    if(pos >= k){
        return verificaMappa(mappa, tab_risorse, tab_target, sol, n, k);
    }
    for(i=0; i<n; i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos].coordinate = val[i];
            if(piazzaRisorseSuMappaR(mappa, tab_risorse, tab_target, pos+1, val, sol, mark, n, k))
                return 1;
            mark[i] = 0;
        }
    }
    return 0;
}

int piazzaRisorseSuMappa(mappa_t mappa, tab_risorse_t tab_risorse, tab_target_t tab_target,
                         int *passed_sol, int k, int n, int costo, int elementi_selezionati){
    int i, j, l, ret,
        *mark = calloc(sizeof(int), n);

    coordinate_t *val = malloc(sizeof(coordinate_t) * n);
    risorse_coordinate_t *sol = malloc(sizeof(risorse_coordinate_t) * elementi_selezionati);

    for(i=0, l=0; i<mappa->n_righe; i++)
        for(j=0; j<mappa->n_colonne; j++){
            val[l].r = i;
            val[l].c = j;
            l++;
        }

    for(i=0, l=0; i<k; i++){ // per ogni risorsa
        for(j=0; j<passed_sol[i]; j++){
            sol[l++].risorsa = tab_risorse->risorse[i];
        }
    }

    ret = piazzaRisorseSuMappaR(mappa, tab_risorse, tab_target, 0, val, sol, mark, n-1, elementi_selezionati);
    free(val);
    free(sol);
    return ret;
}

/* SELEZIONE RISORSE IN BASE AL BUDGET
 * La funzione seleziona il primo risultato completamente valido,
 * ritornando: - "1" se la soluzione e` completamente valida (in tal caso la ricorsione termina)
 *             - "0" se la soluzione non e` stata (ancora) trovata
 */
int selezionaInBaseAlBudgetR(mappa_t mappa, tab_risorse_t tab_risorse, tab_target_t tab_target, int budget, int valore_alleato_massimo, int valore_nemico_massimo,
               int pos, int *val, int *sol, int n, int k, int costo, int elementi_selezionati){ // n e` n+1
    int i, tmp_costo, tmp_val_all, tmp_val_nem, ret;
    // Pruning
    if(costo > budget || elementi_selezionati > n)
        return 0;

    // Terminazione
    if(pos >= k){
        tmp_val_all = tmp_val_nem = 0;
        for(i=0; i<tab_risorse->n_risorse; i++){
            tmp_val_all += sol[i] * tab_risorse->risorse[i].difesa;
            tmp_val_nem += sol[i] * tab_risorse->risorse[i].attacco;
        }

        // Pruning
        if(tmp_val_all < valore_alleato_massimo || tmp_val_nem < valore_nemico_massimo)
            return 0;

        ret = piazzaRisorseSuMappa(mappa, tab_risorse, tab_target, sol, k, n-1, costo, elementi_selezionati);
        return ret;
    }

    // Ricorsione
    for(i=0; i<n; i++){
        sol[pos]=val[i];
        tmp_costo = tab_risorse->risorse[pos].costo * sol[pos];
        costo += tmp_costo;
        elementi_selezionati += val[i];

        if(selezionaInBaseAlBudgetR(mappa, tab_risorse, tab_target, budget, valore_alleato_massimo, valore_nemico_massimo, pos+1, val, sol, n, k, costo, elementi_selezionati))
            return 1;

        costo -= tmp_costo;
        elementi_selezionati -= val[i];
    }
    return 0;
}

int selezionaInBaseAlBudget(mappa_t mappa, tab_target_t tab_target, tab_risorse_t tab_risorse, int budget, int valore_alleato_massimo, int valore_nemico_massimo){
    int i, *val, *sol, k, n, ret;

    k = tab_risorse->n_risorse;
    n = mappa->n_righe * mappa->n_colonne;

    sol  = malloc(sizeof(int) * k);
    val  = malloc(sizeof(int) * n);
    for(i=0; i<n; i++)
        val[i] = i;

    ret = selezionaInBaseAlBudgetR(mappa, tab_risorse, tab_target, budget, valore_alleato_massimo, valore_nemico_massimo, 0, val, sol, n, k, 0, 0);
    free(val);
    free(sol);
    return ret;
}

void risolviMappa(mappa_t mappa, tab_target_t tab_target, tab_risorse_t tab_risorse, int budget){
    int all_max=-1, nem_max=-1; // alleato e nemico con valore maggiore
    int i;
    target_t tmp_target;

    for(i=0; i<tab_target->n_target; i++){
        tmp_target = tab_target->target[i];
        if(tmp_target.tipo == alleato){
            if(all_max == -1 || tmp_target.valore_riferimento > tab_target->target[all_max].valore_riferimento)
                all_max = i;
        }else if(tmp_target.tipo == nemico){
            if(nem_max == -1 || tmp_target.valore_riferimento > tab_target->target[nem_max].valore_riferimento)
                nem_max = i;
        }
    }
    all_max = (all_max==-1) ? 0 : tab_target->target[all_max].valore_riferimento;
    nem_max = (nem_max==-1) ? 0 : tab_target->target[nem_max].valore_riferimento;

    qsort(tab_risorse->risorse, (size_t)tab_risorse->n_risorse, sizeof(risorsa_t), cmpfunc);

    printf("Risolvendo la mappa con budget %d...\n", budget);
    if(selezionaInBaseAlBudget(mappa, tab_target, tab_risorse, budget, all_max, nem_max))
        printf("Mappa risolta");
    else
        printf("Non e` possibile risolvere la mappa con le impostazioni indicate");
}