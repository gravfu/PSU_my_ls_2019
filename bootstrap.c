/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main example
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/sysmacros.h>
#include "./include/my.h"

void print_file_name(char const *name)
{
    int i;
    int last_bs = 0;
    for (i = 0; name[i] != '\0'; i++)
        if (name[i] == '/')
            last_bs = i;
    my_putstr("Name: ");
    my_putstr(&name[last_bs + 1]);
    my_putchar('\n');
}

void print_file_one(struct stat *sb)
{
    my_putstr("Type: ");
    switch (sb->st_mode & S_IFMT) {
    case S_IFBLK: my_putchar('b');
        break;
    case S_IFCHR: my_putchar('c');
        break;
    case S_IFDIR: my_putchar('d');
        break;
    case S_IFIFO: my_putchar('p');
        break;
    case S_IFLNK: my_putchar('l');
        break;
    case S_IFREG: my_putchar('f');
        break;
    case S_IFSOCK: my_putchar('s');
        break;
    default: my_putchar('u');
        break;
    }
    my_putchar('\n');
}

void print_file_two(struct stat *sb)
{
    my_putstr("Inode: ");
    my_put_nbr(sb->st_ino);
    my_putchar('\n');

    my_putstr("Hard Link: ");
    my_put_nbr(sb->st_nlink);
    my_putchar('\n');

    my_putstr("Size: ");
    my_put_nbr(sb->st_size);
    my_putchar('\n');
}

void print_file_three(struct stat *sb)
{
    my_putstr("Allocated space: ");
    my_put_nbr(sb->st_blocks);
    my_putchar('\n');

    my_putstr("Minor: ");
    my_put_nbr(minor(sb->st_rdev));
    my_putchar('\n');

    my_putstr("Major: ");
    my_put_nbr(major(sb->st_rdev));
    my_putchar('\n');

    my_putstr("UID: ");
    my_put_nbr(minor(sb->st_uid));
    my_putchar('\n');

    my_putstr("GID: ");
    my_put_nbr(minor(sb->st_gid));
    my_putchar('\n');
}


void print_file(struct stat *sb)
{
    char const *file = av[1];
    struct stat sb;
    int error = stat(file, &sb);
    if (error == 0) {
        print_file_name(file);
        print_file_one(&sb);
        print_file_two(&sb);
        print_file_three(&sb);
    } else {
        my_putstr("File not found\n");
        return 84;
    }
}
