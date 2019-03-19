#include <stdio.h>
#include <stdlib.h>
int mediaMobile(int V[], int v, int k, float M[]);
int main()
{
    int V[30], V_s, M_s, k, i;
    float M[30];

    do{
        printf("Inserisci dimensione vettore V: ");
        scanf("%i", &V_s);
    }while(V_s <= 0 || V_s > 30);

    for (i=0; i<V_s; i++){
        printf("V[%i]: ", i);
        scanf("%i%*c", &V[i]);
    }

    printf("Inserire k: ");
    scanf("%i", &k);
    M_s = mediaMobile(V, V_s, k, M);

    for(i=0; i<M_s; i++){
        printf("%f, ", M[i]);
    }
    return 0;
}

int mediaMobile(int V[], int v, int k, float M[]){
    int somma, i_max = v-k, i,j;
    float media;

    for(i=0; i<=i_max; i++){
        somma = 0;
        for(j=i; j<(k+i); j++){
            somma += V[j];
        }
        media = (float)somma / k;
        M[i] = media;
    }
    return i;
}
