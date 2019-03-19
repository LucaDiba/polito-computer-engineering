#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int consonanti(char *word){
    int i, cons = 0, n = strlen(word);
    char lettera;
    for(i=0; i<n; i++){
        lettera = word[i];
        switch(lettera){
            case 'a':case 'A':case 'e':case 'E':case 'i':case 'I':case 'o':case 'O':case 'u':case 'U':
                break;
            default:
                cons++;
        }
    }
    return cons;
}

int main(int argc, char *argv[])
{
    FILE *fp, *fp_2, *fp_3;
    char fn[10+1], parola[20+1];
    int i, n;

    scanf("%s%*c", fn);
    fp = fopen(fn, "r");
    fp_2 = fopen("file_2.txt", "w");
    fp_3 = fopen("file_3.txt", "w");
    if(!fp || !fp_2 || !fp_3)return -1;


    fscanf(fp, "%i %s", &n, parola);
    char word[n][20+1];
    for(i=0; i<n; i++){
        fscanf(fp, "%s", word[i]);

        if(parola[0] < word[i][0]){
            fprintf(fp_2, "%s\n", word[i]);
        }
        if(consonanti(word[i]) > consonanti(parola)){
            fprintf(fp_3, "%s\n", word[i]);
        }
    }
    fclose(fp);
    fclose(fp_2);
    fclose(fp_3);
    return 0;
}
