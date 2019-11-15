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

void print_perm(struct stat *sb, char *str)
{
    my_ls_l_print_one(sb);
    my_ls_l_print_two(sb);
    my_ls_l_print_three(sb);
    my_ls_l_print_four(sb);
}

void my_ls_l_two(char *str, int const *arg, char const *dir_const, int is_file)
{
    struct stat sb;
    char *file = my_strdup(dir_const);

    if (is_file == 0) {
        file = my_strcat(file, "/");
        file = my_strcat(file, str);
    }
    int error = stat(file, &sb);
    if (error == 0) {
        print_perm(&sb, str);
        my_putchar(' ');
        my_putstr(str);
        my_putchar('\n');
    } else {
        my_putstr("ls: cannot access '");
        my_putstr(str);
        my_putstr("': No such file or directory\n");
    }
    if (file != NULL) {
        free(file);
        file = NULL;
    }
}

int my_ls_get_blocks(char **tab, int const *arg, char const *dir_const,
                    int is_file)
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
        nb_block += sb.st_blocks;
        if (file != NULL) {
            free(file);
            file = NULL;
        }
    }
    return nb_block;
}

void my_ls_l(char **tab, int const *arg, char const *dir_const, int is_file)
{
    char *tmp = NULL;
    int nb_block;

    if (is_file == 0) {
        nb_block = my_ls_get_blocks(tab, arg, dir_const, is_file);
        my_putstr("total ");
        my_put_nbr(nb_block/2);
        my_putchar('\n');
    }
    for (int i = 0; tab[i] != NULL; i++) {
        tmp = my_strdup(tab[i]);
        my_ls_l_two(tab[i], arg, dir_const, is_file);
    }
}