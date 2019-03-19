#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    int n[5], i, j;
    int col[5] = {0};
    float media_tmp;

    for(i=0; fscanf(fp, "%i %i %i %i %i", &n[0], &n[1], &n[2], &n[3], &n[4]) != EOF; i++){
        media_tmp = (float)(n[0] + n[1] + n[2] + n[3] + n[4])/5;
        printf("Media riga %i\t\t%.1f\n", i+1, media_tmp);
        for(j=0; j<5; j++){
            col[j] += n[j];
        }
    }
    for(j=0; j<5; j++){
        media_tmp = (float)col[j]/i;
        printf("Media colonna %i:\t%.1f\n", j, media_tmp);
    }

    fclose(fp);
    return 0;
}
