/*
** EPITECH PROJECT, 2019
** my_ls_l.c
** File description:
** my_ls -l
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "./include/my.h"
#include "./include/directory.h"
#include "./include/ls_l_print.h"

void print_perm(struct stat *sb)
{
    my_ls_l_print_one(sb);
    my_ls_l_print_two(sb);
    my_ls_l_print_three(sb);
    my_ls_l_print_four(sb);
}

int my_ls_l_two(char *str, char const *dir_const, int is_file)
{
    struct stat sb;
    char *file = my_strdup(dir_const);
    int error = 0;

    if (is_file == 0) {
        file = my_strcat(file, "/");
        file = my_strcat(file, str);
    }
    int error2 = stat(file, &sb);
    if (error2 != -1) {
        print_perm(&sb);
        my_putchar(' ');
        my_putstr(str);
        my_putchar('\n');
    } else {
        my_putstr("ls: cannot access '");
        my_putstr(str);
        my_putstr("': No such file or directory\n");
        error = 84;
    }
    if (file != NULL) {
        free(file);
        file = NULL;
    }
    return error;
}

int my_ls_get_blocks(char **tab, char const *dir_const)
{
    char *file;
    struct stat sb;
    int nb_block = 0;
    int error;

    for (int i = 0; tab[i] != NULL; i++) {
        file = my_strdup(dir_const);
        file = my_strcat(file, "/");
        file = my_strcat(file, tab[i]);
        error = stat(file, &sb);
        if (error != -1)
            nb_block += sb.st_blocks;
        if (file != NULL) {
            free(file);
            file = NULL;
        }
    }
    return nb_block;
}

int my_ls_l(char **tab, char const *dir_const, int is_file)
{
    int nb_block;
    int error = 0;

    if (is_file == 0) {
        nb_block = my_ls_get_blocks(tab, dir_const);
        my_putstr("total ");
        my_put_nbr(nb_block/2);
        my_putchar('\n');
    }
    for (int i = 0; tab[i] != NULL; i++) {
        if(my_ls_l_two(tab[i], dir_const, is_file) == 84)
            error = 84;
    }
    return error;
}