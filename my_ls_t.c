/*
** EPITECH PROJECT, 2019
** my_advanced_sort_word_array.c
** File description:
** Advancerd Sort Word array
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "./include/my.h"

time_t my_ls_t_cmp(char *str1, char *str2)
{
    struct stat sb1;
    struct stat sb2;

    stat(str1, &sb1);
    stat(str2, &sb2);
    return (sb2.st_mtime - sb1.st_mtime);
}

int my_aswa_len_t(char **tab)
{
    int i;

    for (i = 0; tab[i] != 0; i++);
    return i;
}

void my_aswa_swap_str_t(char **str_one, char **str_two)
{
    char *swap;

    swap = *str_one;
    *str_one = *str_two;
    *str_two = swap;
}

void my_aswa_swap_t(char **array, int j, char const *dir, int is_file)
{
    char *str1 = NULL;
    char *str2 = NULL;
    if (is_file == 0) {
        str1 = my_strdup(dir);
        str1 = my_strcat(str1, "/");
        str1 = my_strcat(str1, array[j]);
        str2 = my_strdup(dir);
        str2 = my_strcat(str2, "/");
        str2 = my_strcat(str2, array[j + 1]);
    }
    if (my_ls_t_cmp(str1, str2) > 0) {
        my_aswa_swap_str_t(&array[j], &array[j + 1]);
    }
}

int my_ls_t(char **tab, char const *dir, int is_file)
{
    int const len = my_aswa_len_t(tab);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            my_aswa_swap_t(tab, j, dir, is_file);
        }
    }
    return 0;
}