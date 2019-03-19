#include <stdio.h>
#include <memory.h>
#include "koala.h"

int soluzionePotenzialmenteValida(int *occorrenze, int n, int m, Vincoli vincoli){
    int i;
    for(i=0; i<n; i++)
        if(occorrenze[i] > m)
            return 0;
    return 1;
}
int soluzioneValida(int *sol, TabKoala tab_koala, TabFamiglie tab_famiglie, Vincoli vincoli){
	int i, j, n_koala = tab_koala->n, flag;
	
	//FAMIGLIE NEMICHE
	if(vincoli.famiglie)
		for(i=0; i<n_koala; i++)
			for(j=i; j<n_koala; j++)
				if(sol[i] == sol[j]) //stesso albero
					if((tab_famiglie->famiglie_nemiche)[tab_koala->koala[i].id_famiglia][tab_koala->koala[j].id_famiglia] == 1) //famiglie nemiche
						return 0;

	//ALBERI SU CUI PUO' VIVERE KOALA
	if(vincoli.habitat){
		for(i=0; i<n_koala; i++){
			flag = 0;
			for(j=0; j<(tab_koala->koala)[i].n_alberi_ammessi && flag == 0; j++)
				if(((tab_koala->koala)[i].id_alberi_ammessi)[j] == sol[i])
					flag = 1;
	        if(flag == 0)
	            return 0;
		}
	}

	return 1;
}

void determinaAllocazioneR(int pos, int *val, int *sol, int n, int k, TabKoala tab_koala, TabFamiglie tab_famiglie, int *occorrenze, int m, Vincoli vincoli){
    int i;
    if(soluzionePotenzialmenteValida(occorrenze, n, m, vincoli)){
        if(pos>=n){
            if(soluzioneValida(sol, tab_koala, tab_famiglie, vincoli)){
                for(i=0; i<n; i++)
        	        printf("%d ", sol[i]);
                printf("\n");
            }
            return;
        }
        for(i=0; i<n; i++){
            sol[pos] = val[i];
            occorrenze[sol[pos]]++;
            determinaAllocazioneR(pos+1, val, sol, n, k, tab_koala, tab_famiglie, occorrenze, m, vincoli);
            occorrenze[sol[pos]]--;
        }
    }
}

void determinaAllocazione(int max_per_albero, TabKoala tab_koala, TabFamiglie tab_famiglie, Vincoli vincoli){
	int i, *sol, *val, n_koala=tab_koala->n, n_alberi_min, *occorrenze;

	sol = malloc(n_koala * sizeof(int));
	val = malloc(n_koala * sizeof(int));
    occorrenze = calloc(n_koala, sizeof(int));

	for(i=0; i<n_koala; i++)
		val[i]=i;

	n_alberi_min = n_koala/max_per_albero;
	determinaAllocazioneR(0, val, sol, n_koala, i, tab_koala, tab_famiglie, occorrenze, max_per_albero, vincoli);
}

TabKoala acquisisciKoala(char *filename){
	FILE *fp=NULL;
	int i, j, tmp_n_alberi, n_koala;
	Koala *koala;
	TabKoala tab_koala = malloc(sizeof(TabKoala));

	if((fp=fopen(filename, "r")) == NULL){
		printf("Errore nella lettura dei koala");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &n_koala);
	koala = malloc(n_koala * sizeof(Koala));
	for(i=0; i<n_koala; i++){
		fscanf(fp, " %d", &tmp_n_alberi);
		koala[i].n_alberi_ammessi = tmp_n_alberi;
		koala[i].id_alberi_ammessi = malloc(tmp_n_alberi * sizeof(int));
		for(j=0; j<tmp_n_alberi; j++){
			fscanf(fp, " %d", &(koala[i].id_alberi_ammessi[j]));
		}
	}
	tab_koala->koala = koala;
	tab_koala->n = n_koala;
	return tab_koala;
}

TabFamiglie acquisisciFamiglie(char *fam_filename, char *nem_filename, TabKoala tab_koala){
	TabFamiglie tab_famiglie = malloc(sizeof(TabFamiglie));
	FILE *fp=NULL;
	int i, j, tmp_n_koala, tmp_id_koala, n_fam,
			tmp_fam_1, tmp_fam_2,
			**famiglie_nemiche;

	if((fp=fopen(fam_filename,"r")) == NULL){
		printf("Errore nella lettura delle famiglie");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &n_fam),
			famiglie_nemiche = malloc(n_fam * sizeof(int));
	for(i=0; i<n_fam; i++){
		famiglie_nemiche[i] = calloc(n_fam, sizeof(int));
		fscanf(fp, " %d", &tmp_n_koala);
		for(j=0; j<tmp_n_koala; j++){
			fscanf(fp, " %d", &tmp_id_koala);
			tab_koala->koala[tmp_id_koala].id_famiglia = i;
		}
	}
	fclose(fp);

	if((fp=fopen(nem_filename,"r")) == NULL){
		printf("Errore nella lettura dei nemici");
		exit(EXIT_FAILURE);
	}
	while(fscanf(fp, " %d %d", &tmp_fam_1, &tmp_fam_2) != EOF){
		famiglie_nemiche[tmp_fam_1][tmp_fam_2] = 1;
		famiglie_nemiche[tmp_fam_2][tmp_fam_1] = 1;
	}
	fclose(fp);
	tab_famiglie->famiglie_nemiche = famiglie_nemiche;
	tab_famiglie->n = n_fam;
	return tab_famiglie;
}