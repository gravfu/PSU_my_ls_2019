/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "include/my.h"
#include "include/directory.h"
#include <stdio.h>

int my_ls_r(char **tab, char const *directory, int const *params)
{
    int error = 0;
    struct stat sb;
    char *file = NULL;

    for (int i = 0; tab[i] != NULL; i++){
        file = my_strdup(directory);
        file = my_strcat(file, "/");
        file = my_strcat(file, tab[i]);
        tab[i] = file;
    }
    for (int i = 0; tab[i] != NULL && (stat(tab[i], &sb) != -1); i++){
        if (sb.st_mode & S_IFDIR) {
            my_putstr("\n");
            if (open_directory(tab[i], params) == 84)
                error = 84;
        }
    }
    return error;
}