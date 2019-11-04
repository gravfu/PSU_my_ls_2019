/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "./include/my.h"

int my_advanced_sort_word_array(char **tab,
                                int(*cmp)(char const *, char const *));

/* TO DO

char **my_realloc_with_value(char **to_cpy, char *str)
{
    char **tab = malloc(sizeof(to_cpy) + 1);

    for (int i = 0; tab[i] != NULL; i++) {

    }
} */

void open_directory(char const *directory)
{
    DIR *dir;
    struct dirent *sd = NULL;
    char **tab = malloc(sizeof(char *) * 9999999);
    int i = 0;

    dir = opendir(directory);
    if (dir == NULL) {
        my_putstr("ls: cannot access 'fdf': No such file or directory");
        exit (84);
    }
    sd = readdir(dir);
    while (sd != NULL) {
        tab[i] = sd->d_name;
        sd = readdir(dir);
        i++;
    }
    my_advanced_sort_word_array(tab, &my_strcmp);
    tab[i] = NULL;
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
}