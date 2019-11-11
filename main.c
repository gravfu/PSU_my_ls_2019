/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

#include "include/directory.h"
#include "include/my.h"

#include <stdlib.h>

void check_params_two(int *params, char *str)
{
    int i = 0;

    for (;str[i] != '\0'; i++) {
        switch (str[i]) {
        case 'l' : params[1] = 1;
            break;
        case 'R' : params[2] = 1;
            break;
        case 'd' : params[3] = 1;
            break;
        case 'r' : params[4] = 1;
            break;
        case 't' : params[5] = 1;
            break;
        default: params[0] = 1;
            break;
        }
    }
    if (params[0] != 0)
    {
        my_putstr("CHECK YOUR FUCKING PARAMS\n");
        exit(84);
    }
}

void check_params(int *params, int ac, char **av)
{
    for (int i = 0; i < ac; i++) {
        if (av[i][0] == '-')
            check_params_two(params, &av[i][1]);
    }
}

int main(int argc, char **argv)
{
    int params[6] = {0, 0, 0, 0, 0, 0};
    int check_nothing = 0;

    check_params(params, argc, argv);
    if (argc == 1) {
        open_directory(".", params);
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            open_directory(argv[i], params);
            check_nothing = 1;
        }
    }
    if (check_nothing == 0)
        open_directory(".", params);
    return 0;
}