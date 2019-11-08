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
#include "./include/directory.h"


/* TO DO

char **my_realloc_with_value(char **to_cpy, char *str)
{
    char **tab = malloc(sizeof(to_cpy) + 1);

    for (int i = 0; tab[i] != NULL; i++) {

    }
} */

void my_print_ls(char **tab, char const *directory, int const *params)
{
    if (params[4] == 1)
        my_advanced_sort_word_array(tab, &my_strcmp_inv);
    else
        my_advanced_sort_word_array(tab, &my_strcmp);
    if (params[2] == 1)
        my_putstr("TO DO\n");
    if (params[3] == 1)
        my_putstr("TO DO\n");
    if (params[5] == 1)
        my_putstr("TO DO\n");
    //if (params[1] == 1)
        //my_ls_l(tab, params, directory);

    if (params[1] == 1)
        my_ls_l(tab, params, directory);
    else {
        for(int i = 0; tab[i] != NULL; i++) {
            my_putstr(tab[i]);
            my_putchar('\n');
        }
    }
}

void open_directory(char const *directory, int const *params)
{
    DIR *dir;
    struct dirent *sd = NULL;
    char **tab = malloc(sizeof(char *) * 9999999);
    int i = 0;

    dir = opendir(directory);
    if (dir == NULL) {
        my_putstr("ls: cannot access 'fdf': No such file or directory\n");
        exit (84);
    }
    sd = readdir(dir);
    while (sd != NULL) {
        if (sd->d_name[0] != '.') {
            tab[i] = sd->d_name;
            i++;
        }
        sd = readdir(dir);
    }
    tab[i] = NULL;
    my_print_ls(tab, directory, params);
}