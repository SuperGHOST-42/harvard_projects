#include <ctype.h>
#include <stdio.h>
#include <string.h>

int ft_score(char str[]);

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    char word1[50], word2[50];

    printf("Player 1: ");
    scanf("%49s", word1);

    printf("Player 2: ");
    scanf("%49s", word2);

    int score1 = ft_score(word1);
    int score2 = ft_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
    return 0;
}

int ft_score(char str[])
{
    int score = 0;
    int index = 0;

    for (int i = 0, len = strlen(str); i < len; i++)
    {
        if (isalpha(str[i]))
        {
            index = tolower(str[i]) - 'a';
            score += points[index];
        }
    }
    return score;
}
