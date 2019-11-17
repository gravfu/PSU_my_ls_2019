/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

#include <sys/types.h>
#include <sys/stat.h>
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
    if (to_cpy != NULL)
        free(to_cpy);
    tab[i] = my_strdup(str);
    tab[i+1] = NULL;
    return tab;
}

int my_print_ls(char **tab, char const *directory, int const *params,
                int is_file)
{
    int error = 0;

    my_advanced_sort_word_array(tab, &my_strcmp);
    if (params[5] == 1)
        my_ls_t(tab, directory, is_file);
    if (params[4] == 1)
        my_advanced_sort_word_array(tab, &my_strcmp_inv);
    if (params[1] == 1) {
        if (my_ls_l(tab, directory, is_file) == 84)
            error = 84;
    } else
        tab = my_ls_std(tab, is_file, &error);
    return error;
}


char **read_directory_two(int *error, DIR *dir, char const *directory,
                        int const *params)
{
    char **tab = malloc(sizeof(char *) * 2);
    struct dirent *sd = NULL;
    int i = 0;

    tab[0] = NULL;
    tab[1] = NULL;
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
    if (my_print_ls(tab, directory, params, 0) == 84)
        *error = 84;
    return tab;
}

char **read_directory_one(int *error, char const *directory,
                            int const *params)
{
    char **tab = malloc(sizeof(char *) * 2);
    int error2;
    struct stat sb;

    tab[0] = my_strdup(directory);
    tab[1] = NULL;
    error2 = stat(tab[0], &sb);
    if (error2 != -1) {
        if (my_print_ls(tab, directory, params, 1) == 84)
            *error = 84;
    } else {
        *error = 84;
        my_error_handle(directory, 2);
    }
    return tab;
}

int open_directory(char const *directory, int const *params)
{
    DIR *dir;
    int error = 0;
    char **tab = NULL;

    dir = opendir(directory);
    if (params[2] == 1) {
        my_putstr(directory);
        my_putstr(":\n");
    }
    if (dir == NULL || params[3] == 1) {
        tab = read_directory_one(&error, directory, params);
    } else {
        tab = read_directory_two(&error, dir, directory, params);
    }
    if (params[2] == 1)
        if (my_ls_r(tab, directory, params) == 84)
            error = 84;
    return error;
}