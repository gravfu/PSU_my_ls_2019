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

char **my_realloc_s(char **to_cpy, char const *str, int j)
{
    int i;
    char **tab = malloc(sizeof(char *) * (j + 2));

    for (i = 0; to_cpy[i] != NULL; i++) {
        tab[i] = my_strdup(to_cpy[i]);
        free(to_cpy[i]);
    }
    tab[i] = my_strdup(str);
    tab[i+1] = NULL;
    if (to_cpy != NULL)
        free(to_cpy);
    return tab;
}

void my_print_ls(char **tab, char const *directory, int const *params, int is_file)
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
        my_ls_l(tab, params, directory, is_file);
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
    char **tab = malloc(sizeof(char *) * 1);
    int i = 0;

    tab[0] = NULL;
        dir = opendir(directory);
    if (dir == NULL) {
        tab = my_realloc_s(tab, directory, 0);
        i++;
        //my_putstr("ls: cannot access 'fdf': No such file or directory\n");
        tab[i] = NULL;
        my_print_ls(tab, directory, params, 1);
    } else {
        sd = readdir(dir);
        while (sd != NULL) {
            if (sd->d_name[0] != '.') {
                tab = my_realloc_s(tab, sd->d_name, i);
                i++;
            }
            if (dir != NULL)
                sd = readdir(dir);
        }
        tab[i] = NULL;
        my_print_ls(tab, directory, params, 0);
    }
}