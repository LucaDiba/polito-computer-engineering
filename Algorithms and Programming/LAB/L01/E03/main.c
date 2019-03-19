#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int indexOf(int search, int A[], int n);
int wordlen(char word[]);

int main()
{
    FILE *fp = NULL, *fp_s = NULL, *fp_w = NULL;
    int i, n, len, t_len, id, offset, tmp_offset, sost_n[30] = {0};
    char sost[30][200+1], tmp_row[200+2], tmp_str[200+1]; //Nel peggiore dei casi una riga sara' composta da una sola parola

    fp = fopen("src.txt", "r");
    fp_s = fopen("sost.txt", "r");
    fp_w = fopen("dest.txt", "w");
    if(fp == NULL || fp_s == NULL || fp_w == NULL)return -1;
    fscanf(fp_s, "%i", &n);
    for(i=0; i<n; i++){
        fscanf(fp_s, "%i %s", &sost_n[i], sost[i]);
    }

    while(fgets(tmp_row, 200, fp)){
        offset = 0;
        while(sscanf(&tmp_row[offset], "%s%n", tmp_str, &tmp_offset) == 1){
            len = wordlen(tmp_str);
            t_len = strlen(tmp_str);
            id = indexOf(len, sost_n, n);
            if(id > -1){
                fprintf(fp_w, "%s", sost[id]);
                if(len < t_len){
                    printf("-%i %i %s \t\t %s\n", len, t_len, tmp_str, &tmp_str[len]);
                    fprintf(fp_w, "%s", &tmp_str[len]);
                }else{
                    printf("%i %i %s \t\t %s\n", len, t_len, tmp_str, &tmp_str[len]);
                    fprintf(fp_w, "%s", &tmp_str[len]);
                }
            }else{
                fprintf(fp_w, "%s", tmp_str);
            }
            fprintf(fp_w, " ");
            offset += tmp_offset;
        }
        fprintf(fp_w, "%s", "\n");
    }

    fclose(fp);
    fclose(fp_s);
    fclose(fp_w);
    return 0;
}

int indexOf(int search, int A[], int n){
    int i;
    for(i=0; i<n; i++){
        if(search == A[i])
            return i;
    }
    return -1;
}

int wordlen(char word[]){
    int i;
    for(i=0; word[i] > 'A' && word[i] < 'z'; i++);
    return i;
}
