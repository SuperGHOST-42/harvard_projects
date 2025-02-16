#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipagem das funções
int is_numeric_string(char argv[]);
char *get_input();
void rotate(char *text, int key);

int main(int argc, char *argv[])
{
    // Verifica se o número de argumentos é válido e se o segundo argumento é numérico
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1; // Retorna erro se o número de argumentos estiver incorreto
    }

    if (!is_numeric_string(argv[1]))
    {
        printf("Error: Key must be a numeric value\n");
        return 1; // Retorna erro se a chave não for numérica
    }

    // Converte a chave para inteiro
    int key = atoi(argv[1]);

    // Normaliza a chave para o intervalo de 0-25, garantindo que seja não negativa
    key = key % 26;
    if (key < 0)
    {
        key += 26; // Converte para positivo, se necessário
    }

    // Obtém o texto a ser cifrado
    char *text = get_input();
    if (!text) // Verifica se a entrada falhou
    {
        return 1;
    }

    // Cifra e imprime o resultado
    printf("ciphertext: ");
    rotate(text, key);
    printf("\n");

    // Libera a memória alocada
    free(text);

    return 0;
}

/**
 * Verifica se uma string contém apenas dígitos.
 * @param argv: string a ser verificada
 * @return 1 se for numérica, 0 caso contrário
 */
int is_numeric_string(char argv[])
{
    int len = strlen(argv);
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(argv[i])) // Verifica se o caractere não é um dígito
        {
            return 0; // Retorna 0 se encontrar um caractere não numérico
        }
    }
    return 1; // Retorna 1 se todos os caracteres forem dígitos
}

/**
 * Lê a entrada do usuário com suporte a redimensionamento dinâmico.
 * @return ponteiro para a string de entrada (deve ser liberado com free)
 */
char *get_input()
{
    size_t buffer_size = 256; // Tamanho inicial do buffer
    char *buffer = malloc(buffer_size);
    if (!buffer)
    {
        printf("Error: Memory allocation failed\n");
        return NULL; // Retorna NULL se a alocação de memória falhar
    }

    printf("plaintext: ");
    size_t position = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // Redimensiona o buffer, se necessário
        if (position >= buffer_size - 1)
        {
            buffer_size *= 2; // Duplica o tamanho do buffer
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer)
            {
                printf("Error: Memory reallocation failed\n");
                free(buffer);
                return NULL; // Retorna NULL se a realocação de memória falhar
            }
            buffer = new_buffer; // Atualiza o ponteiro do buffer
        }
        buffer[position++] = ch; // Adiciona o caractere ao buffer
    }
    buffer[position] = '\0'; // Termina a string

    return buffer; // Retorna o ponteiro para a string
}

/**
 * Aplica a cifra de César a um texto.
 * @param text: texto a ser cifrado
 * @param key: valor de deslocamento
 */

void rotate(char *text, int key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        // Verifica se é uma letra maiúscula
        if (c >= 'A' && c <= 'Z')
        {
            c = ((c - 'A' + key) % 26) + 'A'; // Aplica a cifra para maiúsculas
        }
        // Verifica se é uma letra minúscula
        else if (c >= 'a' && c <= 'z')
        {
            c = ((c - 'a' + key) % 26) + 'a'; // Aplica a cifra para minúsculas
        }
        // Caracteres não alfabéticos permanecem inalterados
        // (ex.: espaços, pontuação, números)

        // Imprime o caractere (modificado ou não)
        putchar(c);
    }
}
