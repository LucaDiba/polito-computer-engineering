#include <stdio.h>
#include <stdlib.h>
#define max 10

int main()
{
    int numden;
    int denomination[max];
    int coins[max];
    int amount, i;

    printf("enter number of denominations:");
    scanf("%d", &numden);

    printf("enter denominations in cents in decreasing order\n");
    for (i=0; i<numden; i++)
    {
        printf("denomination[%d] = ", i);
        scanf("%d", &denomination[i]);
    }

    printf("enter amount in cents:");
    scanf("%d", &amount);

    for (i=0; i < numden; i++)
    {
        coins[i] = amount / denomination[i];
        amount = amount - (amount/denomination[i])*denomination[i];
        printf("number of  %d cent coins = %d \n", denomination[i], coins[i]);
    }
    return 0;
}


