/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Print my_ls_l print
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "include/my.h"

void my_ls_l_print_one(struct stat *sb)
{
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
    case S_IFREG: my_putchar('-');
        break;
    case S_IFSOCK: my_putchar('s');
        break;
    default: my_putchar('u');
        break;
    }
}

void my_ls_l_print_two(struct stat *sb)
{
    my_putstr(sb->st_mode & S_IRUSR ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWUSR ? 	"w" : "-");
    my_putstr(sb->st_mode & S_IXUSR ? 	"x" : "-");
    my_putstr(sb->st_mode & S_IRGRP ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWGRP ? 	"w" : "-");
    my_putstr(sb->st_mode & S_IXGRP ? 	"x" : "-");
    my_putstr(sb->st_mode & S_IROTH ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWOTH ? 	"w" : "-");
    if (sb->st_mode & S_ISVTX)
        my_putstr("t");
    else if (sb->st_mode & S_IXOTH)
        my_putstr("x");
    else
        my_putstr("-");
    my_putchar(' ');
    my_put_nbr(sb->st_nlink);
    my_putchar(' ');
}

void my_ls_l_print_three(struct stat *sb)
{
    struct passwd *password = getpwuid(sb->st_uid);
    my_putstr(password->pw_name);
    my_putchar(' ');
    struct group *group_file = getgrgid(sb->st_gid);
    my_putstr(group_file->gr_name);
    my_putchar(' ');

    if (sb->st_mode & S_IFCHR) {
        my_put_nbr(major(sb->st_rdev));
        my_putstr(", ");
    }

    my_put_nbr(sb->st_size);
    my_putchar(' ');
}


void my_ls_l_print_four(struct stat *sb)
{
    time_t *the_time = &sb->st_mtime;

    char *file_modif = ctime(the_time);
    file_modif[my_strlen(file_modif) - 1] = '\0';
    int i = 0;
    for (; file_modif[i] != ' ' && file_modif[i] != '\0'; i++);
    i++;
    for (; file_modif[i] != ' ' && file_modif[i] != '\0'; i++)
        my_putchar(file_modif[i]);
    my_putchar(' ');
    i++;
    for (; file_modif[i] != ' ' && file_modif[i] != '\0'; i++)
        my_putchar(file_modif[i]);
    for (; file_modif[i] != ':' && file_modif[i] != '\0'; i++)
        my_putchar(file_modif[i]);
    my_putchar(':');
    i++;
    for (; file_modif[i] != ':' && file_modif[i] != '\0'; i++)
        my_putchar(file_modif[i]);
}