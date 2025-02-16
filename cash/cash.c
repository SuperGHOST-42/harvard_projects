#include <stdio.h>

int main(void)
{
    int cents;

    // Solicita ao usuário o valor do troco
    do
    {
        printf("Change owed (in cents): ");
        if (scanf("%d", &cents) != 1)
        {
            while (getchar() != '\n')
                ;
            cents = -1;
        }
    }
    while (cents < 0);

    int coins = 0;
    int denominations[] = {25, 10, 5, 1};

    // Calcula o número mínimo de moedas
    for (int i = 0; i < 4; i++)
    {
        coins += cents / denominations[i];
        cents %= denominations[i];
    }

    printf("%d\n", coins);
    return 0;
}
