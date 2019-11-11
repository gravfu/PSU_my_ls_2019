/*
** EPITECH PROJECT, 2019
** my_ls_l.c
** File description:
** my_ls -l
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
#include "./include/my.h"
#include "./include/directory.h"

void print_perm(struct stat *sb, char *str)
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
    my_putstr(sb->st_mode & S_IRUSR ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWUSR ? 	"w" : "-");
    my_putstr(sb->st_mode & S_IXUSR ? 	"x" : "-");
    my_putstr(sb->st_mode & S_IRGRP ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWGRP ? 	"w" : "-");
    my_putstr(sb->st_mode & S_IXGRP ? 	"x" : "-");
    my_putstr(sb->st_mode & S_IROTH ? 	"r" : "-");
    my_putstr(sb->st_mode & S_IWOTH ? 	"w" : "-");
    my_putstr(sb->st_mode & S_IXOTH ? 	"x" : "-");
    my_putchar(' ');
    my_put_nbr(sb->st_nlink);
    my_putchar(' ');
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
        my_putstr("Total: ");
        my_put_nbr(nb_block/2);
        my_putchar('\n');
    }
    for (int i = 0; tab[i] != NULL; i++) {
        tmp = my_strdup(tab[i]);
        my_ls_l_two(tab[i], arg, dir_const, is_file);
    }
}