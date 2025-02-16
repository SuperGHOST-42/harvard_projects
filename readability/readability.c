#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(const char str[]);
int count_words(const char str[]);
int count_sentences(const char str[]);

const float COLEMAN_LIAU_LETTER_WEIGHT = 0.0588;
const float COLEMAN_LIAU_SENTENCE_WEIGHT = 0.296;
const float COLEMAN_LIAU_CONSTANT = 15.8;

const int size = 1000;

int main(void)
{
    char text[size];

    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    int total_letters = count_letters(text);
    int total_words = count_words(text);
    int total_sentences = count_sentences(text);

    float L = total_letters / (float) total_words * 100;
    float S = total_sentences / (float) total_words * 100;

    int index = round(COLEMAN_LIAU_LETTER_WEIGHT * L - COLEMAN_LIAU_SENTENCE_WEIGHT * S -
                      COLEMAN_LIAU_CONSTANT);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return 0;
}

int count_letters(const char str[])
{
    int len = strlen(str), letters = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
        {
            letters++;
        }
    }
    // printf("Letters: %i\n", letters);
    return letters;
}

int count_words(const char str[])
{
    int words = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        // Incrementa o contador se encontrar um espaço e o próximo caractere não for outro espaço
        // ou o final da string
        if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
        {
            words++;        }
    }

    // Adiciona uma palavra para o primeiro grupo de caracteres (se não começar com espaço)
    if (str[0] != '\0' && str[0] != ' ')
    {
        words++;
    }

    return words;
}

int count_sentences(const char str[])
{
    int len = strlen(str), sentences = 0;

    for (int i = 0; i < len; i++)
    {
        if ((str[i] == '.') || (str[i] == '?') || (str[i] == '!'))
        {
            sentences++;
        }
    }
    // printf("Sentences: %i\n", sentences);
    return sentences;
}
