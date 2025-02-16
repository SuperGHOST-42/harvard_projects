#include <stdio.h>

int main()
{
    char str[100];

    printf("what's your name? ");
    scanf(" %[^\n]s", str);

    printf("hello, %s\n", str);
}
