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

char **my_ls_std(char **tab, int is_file, int *error)
{
    int error2;
    struct stat sb;

    for (int i = 0; tab[i] != NULL; i++) {
        error2 = stat(tab[i], &sb);
        if(error2 == -1 && is_file == 1) {
            my_error_handle(tab[i], 2);
            *error = 84;
        } else {
            my_putstr(tab[i]);
            my_putchar('\n');
        }
    }
    return tab;
}