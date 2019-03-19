#include <stdio.h>
#include "header.h"

int main() {
    int i,n, V[MAX];
    V[0]=0;
    for(i=1;i<MAX; V[i++]=-1);
    while(scanf("%d", &n)) {
        if(n==-1)break;
        if(n<0 || n>MAX){
            printf("Inserire un numero compreso tra 0 e %d", MAX);
            continue;
        }
        for(i=0;i<=n;i++)
            printf("%d ", H(i, V));
    }
    return 0;
}
