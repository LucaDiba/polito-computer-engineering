#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char tmp_row[200+2], tmp_str[25+1], tmp_char, sequenze[20][5+2], flag;
    FILE *fp_s = NULL, *fp = NULL;
    int tmp_count, k, i, j, l, n_word, controlla, sequenze_len[20], parola_valida;

    fp_s = fopen("sequenze.txt", "r");
    fp = fopen("testo.txt", "r");
    if(fp_s == NULL || fp == NULL)return -1;

    fscanf(fp_s, "%i%*c", &k);
    for(i=0; i<k; i++){
        fscanf(fp_s, "%s%*c", sequenze[i]);
        sequenze_len[i] = strlen(sequenze[i]);
    }

    for(i=0; i<k; i++){
        printf("%s\n", sequenze[i]);
        n_word = 1;
        while(fscanf(fp, "%s", tmp_str) != EOF){
            parola_valida = 1;
            tmp_count = 0;
            for(j=0; j<strlen(tmp_str); j++){
                tmp_char = tmp_str[j];
                if(isalnum(tmp_char)){
                    if(parola_valida == 1){
                        if(tolower(sequenze[i][tmp_count]) == tolower(tmp_char)){
                            tmp_count ++;
                            if(tmp_count == sequenze_len[i]){
                                controlla = 0;
                                for(l=j-(sequenze_len[i]-1); isalnum(tmp_str[l]); l++)
                                    printf("%c", tmp_str[l]);
                                printf(" %i\n", n_word);
                                parola_valida = 0;
                            }
                        }else{
                            parola_valida = 0;
                        }
                    }
                }else{
                    if(tmp_char == '\''){
                        tmp_count = 0;
                        n_word++;
                        parola_valida = 1;
                    }else{
                        break;
                    }
                }
            }
            n_word++;
        }
        printf("\n");
        fseek(fp, 0, SEEK_SET);
    }


    fclose(fp_s);
    fclose(fp);
    return 0;
}
