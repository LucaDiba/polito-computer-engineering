#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float valutaIntegrale(int from, int to, int n, float *c, int M){
    int j,k;
    float x, tmp, cj, sum = 0.0;
    float h = (float)(to-from)/M;
    for(k=0; k<=(M-1); k++){
        x = h*k + h/2;
        tmp = 0;
        for(j=0; j<n+1; j++){
            cj = c[j] * pow(x, j);
            tmp += cj;
            sum += cj;
        }
        printf("Da %i a %f (medio %f) vale:\t%f\n", k, k+h, x, tmp);
    }
    return h*sum;
}
float valutaIntegraleHorner(int from, int to, int n, float *c, int M){
    int i,k;
    float c1 = c[1];
    float x, tmp, sum = 0.0;
    float h = (float)(to-from)/M;
    for(k=0; k<=(M-1); k++){
        x = h*k + h/2;
        tmp = 0.0;
        for(i=n; i>=0; i--){
            tmp = tmp*x + c[i];
        }
        sum += tmp;
        printf("Da %i a %f (medio %f) vale:\t%f\n", k, k+h, x, tmp);
    }
    return h*sum;
}

int main()
{
    float val;
    int from, to, n;
    double M;

    /*printf("Grado polinomio: ");
    scanf("%i%*c", &n);
    float c[n+1];
    for(i=0;i<n+1;i++){
        printf("Coefficiente c(%i): ", i);
        scanf("%f%*c", &c[i]);
    }
    printf("Estremi di integrazione (da a): ");
    scanf("%i %i%*c", &from, &to);
    printf("Sottointervalli: ");
    scanf("%i", &M);*/
    n = 3;
    float c[] = {46, 12, -9, 1};
    from = 0; to = 10;
    M = 20;

    val = valutaIntegraleHorner(from, to, n, c, M);
    printf("L'integrale vale: %f\n", val);

    return 0;
}
