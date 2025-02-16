#include <stdio.h>

// Função para imprimir uma linha com espaços e hashes
void print_row(int spaces, int hashes)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < hashes; i++)
    {
        printf("#");
    }
    printf("\n");
}

int main()
{
    int height;

    // Solicita ao usuário a altura da pirâmide
    printf("Height: ");

    // Certifica-se de que a altura é positiva
    while (scanf("%i", &height) != 1 || height < 1)
    {
        printf("Por favor, insira um número inteiro positivo: ");
        // Limpa o buffer de entrada
        while (getchar() != '\n')
            ;
    }

    // Construção da pirâmide
    for (int i = 1; i <= height; i++)
    {
        int spaces = height - i; // Calcula os espaços à esquerda
        int hashes = i;          // Calcula o número de hashes
        print_row(spaces, hashes);
    }

    return 0;
}
