/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

#include "include/directory.h"
#include "include/my.h"

int main(int argc, char **argv)
{    
    if (argc == 1)
        open_directory(".");
    else
        for(int i = 1; i < argc; i++)
            open_directory(argv[i]);
    return 0;
}