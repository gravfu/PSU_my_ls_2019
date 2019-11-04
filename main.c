/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main example
*/
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "./include/my.h"

int main(int argc, char **argv)
{
    DIR *dir;
    struct dirent *sd = NULL;
    
    if (argc == 1)
        dir = opendir(".");
    else
        dir = opendir(argv[1]);

    if (dir == NULL) {
        my_putstr("ls: cannot access 'fdf': No such file or directory\n");
        return 84;
    }
    sd = readdir(dir);
    while (sd != NULL) {
        my_putstr(sd->d_name);
        my_putchar('\n');
        sd = readdir(dir);
    }
    return 0;
}