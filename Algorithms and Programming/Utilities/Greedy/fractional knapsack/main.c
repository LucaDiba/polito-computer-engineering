#include <stdio.h>
#include <stdlib.h>
#define maxobjects 20

void knapsack(int n, float *weight, float *value, float capacity) {
  float fraction[maxobjects], stolen = 0.0, residue = capacity;
  int i;

  for (i=0; i<n; i++)
    fraction[i]=0.0;

  for (i=0; i<n && (weight[i] <= residue);i++) {
    fraction[i] = 1.0;
    stolen = stolen + value[i];
    residue = residue - weight[i];
  }

  fraction[i] = residue/weight[i];
  stolen = stolen + (fraction[i]*value[i]);

  printf("Results: \n");
  for(i = 0; i < n; i++)
    printf("Fraction of object (weight = %f and value = %f) = %f\n", weight[i], value[i], fraction[i]);

  printf("Total amount stolen: %f \n", stolen);

}

int main() {
  int n, i ,j;
  float value[maxobjects], weight[maxobjects], capacity, ratio[maxobjects], temp;

  printf ("No. of objects: ");
  scanf ("%d", &n);

  printf ("Weight and value of each object: \n");
  for (i=0; i<n; i++) {
    printf("object: ");
    scanf("%f %f", &weight[i], &value[i]);
  }

  printf ("Capacity of knapsack: ");
  scanf ("%f", &capacity);

  for (i = 0; i < n; i++)
    ratio[i] = value[i]/weight[i];

  for(i = 0; i < n; i++) {
    for(j = i+1; j < n; j++) {
      if(ratio[i]<ratio[j]) {
        temp = ratio[j];
        ratio[j] = ratio[i];
        ratio[i] = temp;

        temp = weight[j];
        weight[j] = weight[i];
        weight[i] = temp;

        temp= value[j];
        value[j]= value[i];
        value[i]= temp;
      }
    }
  }

  knapsack(n, weight, value, capacity);
  return 1;
}

