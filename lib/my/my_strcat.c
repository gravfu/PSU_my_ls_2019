/*
** EPITECH PROJECT, 2019
** my_strcat.c
** File description:
** Concatenates two strings
*/

#include <unistd.h>
#include <stdlib.h>

int my_strlen(char const *str);

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int j = 0;
    char *new = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 1));
    int len = my_strlen(dest);

    while (dest[i] != '\0') {
        new[i] = dest[i];
        i++;
    }
    while (src[j] != '\0') {
        new[i] = src[j];
        i++;
        j++;
    }
    if (dest != NULL)
        free(dest);
    new[i] = '\0';
    dest = new;
    return dest;
}
