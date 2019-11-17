/*
** EPITECH PROJECT, 2019
** error.c
** File description:
** Error print base on
*/

#include <unistd.h>
#include "include/my.h"

void my_putchar_error(char c)
{
    write(2, &c, 1);
}

int my_putstr_error(char const *str)
{
    for (int i = 0;  str[i] != '\0'; i++) {
        my_putchar_error(str[i]);
    }
    return (0);
}

int my_error_handle(char const *av, int error)
{
    my_putstr_error("./my_ls: ");
    if (error == 13) {
        my_putstr_error(av);
        my_putstr_error(": Permission denied\n");
        return 84;
    }
    if (error == 2) {
        my_putstr_error(av);
        my_putstr_error(": No such file or directory\n");
        return 84;
    }
    if (error == 21) {
        my_putstr_error("option requires an argument -- '");
        my_putstr_error(av);
        my_putstr_error("'\nTry 'ls --help' for more information.\n");
        return 84;
    }
    if (error != 0)
        my_put_nbr(error);
    return 84;
}