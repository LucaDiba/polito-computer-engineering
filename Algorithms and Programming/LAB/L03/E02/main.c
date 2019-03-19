#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXN 1000
typedef struct{
    int anno;
    int mese;
    int giorno;
} Data;
typedef struct{
    char codice[5+1];
    char partenza[3+1];
    char arrivo[3+1];
    Data data;
    char vettore[100+1];
} Tabella;
typedef enum {
    r_data, r_origine, r_destinazione, r_vettore, r_end
}comando_e;

void strToUpper(char str[]);
void selezionaDati(Tabella voli[], int voli_s, int selezione);
int leggiComando();
int leggiTabella(Tabella voli[], int max_n);
int dateToInt(int anno, int mese, int giorno);

void cercaVettore(Tabella voli[], int voli_s, char str_src[]);
void cercaDestinazione(Tabella voli[], int voli_s, char str_src[]);
void cercaOrigine(Tabella voli[], int voli_s, char str_src[]);
void cercaData(Tabella voli[], int voli_s, int data_src_from, int data_src_to);


int main()
{
    Tabella voli[MAXN];
    int nDati, selezione;

    nDati = leggiTabella(voli, MAXN);
    if(nDati == -1)return -1;
    printf("Dati acquisiti: %i voli", nDati);

    selezione = leggiComando();
    while(selezione != r_end){
        selezionaDati(voli, nDati, selezione);
        selezione = leggiComando();
    }

    return 0;
}

int leggiTabella(Tabella voli[], int max_n){
    FILE *fp = NULL;
    int n,i;

    fp = fopen("voli.txt", "r");
    if(fp == NULL)return -1;

    fscanf(fp, "%i%*c", &n);
    for(i=0; i<n; i++){
        fscanf(fp, "%s %s %s %d/%d/%d:%*d:%*d:%*d %s%*c", voli[i].codice, voli[i].partenza, voli[i].arrivo, &voli[i].data.anno, &voli[i].data.mese, &voli[i].data.giorno, voli[i].vettore);
    }
    fclose(fp);
    return i;
}

int leggiComando(){
    int selezione;
    char seleziona[8+1];
    printf("\nCerca per:\n- data\n- partenza\n- arrivo\n- vettore\n- esci\n>> ");
    scanf("%s", seleziona);
    strToUpper(seleziona);
    if(strcmp(seleziona, "DATA") == 0){
        selezione = r_data;
    }else if(strcmp(seleziona, "PARTENZA") == 0){
        selezione = r_origine;
    }else if(strcmp(seleziona, "ARRIVO") == 0){
        selezione = r_destinazione;
    }else if(strcmp(seleziona, "VETTORE") == 0){
        selezione = r_vettore;
    }else{
        selezione = r_end;
    }
    return selezione;
}

void selezionaDati(Tabella voli[], int voli_s, int selezione){
    int data_src_from, data_src_to;
    char str_src[64];
    Data from, to;
    switch(selezione){
        case r_data: // data
            printf("Inserire intervallo date nel formato \"DD/MM/YYYY DD/MM/YYYY\" (from to):\n>> ");
            scanf("%d/%d/%d %d/%d/%d", &from.giorno, &from.mese, &from.anno, &to.giorno, &to.mese, &to.anno);
            data_src_from = dateToInt(from.anno, from.mese, from.giorno);
            data_src_to = dateToInt(to.anno, to.mese, to.giorno);
            cercaData(voli, voli_s, data_src_from, data_src_to);
            break;
        case r_origine: // origine
            printf("Inserire codice luogo partenza:\n>> ");
            scanf("%s%*c", str_src);
            cercaOrigine(voli, voli_s, str_src);
            break;
        case r_destinazione: // destinazione
            printf("Inserire codice luogo arrivo:\n>> ");
            scanf("%s%*c", str_src);
            cercaDestinazione(voli, voli_s, str_src);
            break;
        case r_vettore: //vettore
            printf("Inserire vettore:\n>> ");
            scanf("%s%*c", str_src);
            cercaVettore(voli, voli_s, str_src);
    }
}

void cercaData(Tabella voli[], int voli_s, int data_src_from, int data_src_to){
    int i, data_tmp;
    for(i=0; i<voli_s; i++){
        data_tmp = dateToInt(voli[i].data.anno, voli[i].data.mese, voli[i].data.giorno);
        if(data_tmp >= data_src_from && data_tmp <= data_src_to){
            printf("%s\n", voli[i].codice);
        }
    }
}
void cercaOrigine(Tabella voli[], int voli_s, char str_src[]){
    int i;
    strToUpper(str_src);
    for(i=0; i<voli_s; i++){
        if(strcmp(str_src, voli[i].partenza) == 0){
            printf("%s\n", voli[i].codice);
        }
    }
}
void cercaDestinazione(Tabella voli[], int voli_s, char str_src[]){
    int i;
    strToUpper(str_src);
    for(i=0; i<voli_s; i++){
        if(strcmp(str_src, voli[i].arrivo) == 0){
            printf("%s\n", voli[i].codice);
        }
    }
}
void cercaVettore(Tabella voli[], int voli_s, char str_src[]){
    int i;
    strToUpper(str_src);
    for(i=0; i<voli_s; i++){
        if(strcmp(str_src, voli[i].vettore) == 0){
            printf("%s\n", voli[i].codice);
        }
    }
}
int dateToInt(int anno, int mese, int giorno){
    return pow(10, 4)*anno + pow(10, 2)*mese + giorno;
}
void strToUpper(char str[]){
    int i;
    for(i=0; i<strlen(str); i++)
        str[i]=toupper(str[i]);
}