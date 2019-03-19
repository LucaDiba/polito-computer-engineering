#include <stdio.h>
#include <stdlib.h>

void StampaVettore(int A[], int size, char delimitatore[]); //O(n)
int EliminaDoppi(int A[], int size); //O(n^2) // con array ordinato; al più due item uguali; ritorna new_size
int EliminaDuplicati(int A[], int size); //O(n^2)
int Differenza(int U[], int U_l, int I[], int I_l, int D[]); //O(n^2) //Unione, Insertion, EliminaDoppi
int Intersezione(int v1[], int v1_l, int v2[], int v2_l, int A[]); // O(n^2) [O(n) senza sorting dopo Unione]
int Unione(int v1[], int v1_l, int v2[], int v2_l, int U[]); //O(n)
void int_InsertionSort(int A[], int i_0, int size); //O(n^2)

int main(){
    int i,v1[20] = {0},v1_l,
    v2[20] = {0},v2_l,U[40],D[40],I[20];
    int U_l, D_l, I_l;

    printf("Dimensione vettore 1: ");
    scanf("%i", &v1_l);
    printf("Dimensione vettore 2: ");
    scanf("%i", &v2_l);

    for(i=0; i<v1_l; i++){
        printf("v1[%i]: ", i);
        scanf("%i%*c", &v1[i]);
    }
    for(i=0; i<v1_l; i++){
        printf("v2[%i]: ", i);
        scanf("%i%*c", &v2[i]);
    }

    printf("\nVettore 1:\t");
    StampaVettore(v1, v1_l, ", ");
    printf("\nVettore 2:\t");
    StampaVettore(v2, v2_l, ", ");

    int_InsertionSort(v1, 0, v1_l);
    int_InsertionSort(v2, 0, v2_l);
    v1_l = EliminaDuplicati(v1, v1_l);
    v2_l = EliminaDuplicati(v2, v2_l);

    //Unione
    U_l = Unione(v1, v1_l, v2, v2_l, U);
    int_InsertionSort(U, 0, U_l);
    U_l = EliminaDuplicati(U, U_l);
    printf("\n\nUnione:\t\t");
    StampaVettore(U, U_l, ", ");

    I_l = Intersezione(v1, v1_l, v2, v2_l, I);
    int_InsertionSort(I, 0, I_l);
    printf("\nIntersezione:\t");
    StampaVettore(I, I_l, ", ");

    D_l = Differenza(U, U_l, I, I_l, D);
    printf("\nDifferenza:\t");
    StampaVettore(D, D_l, ", ");

    return 0;
}


void int_InsertionSort(int A[], int i_0, int size){
   int i, j, x;
   for(i=i_0; i<size; i++){
      x = A[i];

      j = i-1;
      while((j >= 0) && (x < A[j])){
         A[j + 1] = A[j];
         j--;
      }

      A[j + 1] = x;
   }
}

int Unione(int v1[], int v1_l, int v2[], int v2_l, int U[]){
    int i,j;
    for(i=0; i<v1_l; i++){
        U[i] = v1[i];
    }
    for(j=0; j<v2_l; j++, i++){
        U[i] = v2[j];
    }
    return (v1_l+v2_l);
}

int Intersezione(int v1[], int v1_l, int v2[], int v2_l, int A[]){
    int i,k=0;
    int U_l = v1_l+v2_l;
    int U[U_l];
    U_l = Unione(v1, v1_l, v2, v2_l, U);
    int_InsertionSort(U, 0, U_l);
    for(i=1; i<U_l; i++){
        if(U[i] == U[i-1]){
            A[k] = U[i];
            k++;
            i++;
        }
    }
    return k;
}

int Differenza(int U[], int U_l, int I[], int I_l, int D[]){    //O(n^2)
    int D_l;

    D_l = Unione(U, U_l, I, I_l, D);
    int_InsertionSort(D, 0, D_l);
    D_l = EliminaDoppi(D, D_l);
    return D_l;
}

int EliminaDuplicati(int A[], int size){ // con array ordinato; ritorna new_size    // O(n^2)
    int i,j;
    i=1;
    while(i<size){
        if(A[i] == A[i-1]){
            for(j=i; j<size; j++){
                A[j] = A[j+1];
            }
            size--;
        }else i++;
    }
    return size;
}

int EliminaDoppi(int A[], int size){
    int i,j;
    for(i=1; i<size; i++){
        if(A[i] == A[i-1]){
            for(j=i-1; j+2<size; j++){
                A[j] = A[j+2];
            }
            size -= 2;
            i--;
        }
    }
    return size;
}

void StampaVettore(int A[], int size, char delimitatore[]){
    int i=0;
    for(i=0;i<size;i++){
        printf("%i%s", A[i], delimitatore);
    }
}
