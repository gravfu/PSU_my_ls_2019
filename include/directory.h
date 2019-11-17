/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main my_ls
*/

int open_directory(char const *directory, int const *params);
int my_ls_l(char **tab, char const *dir_const, int is_file);
int my_error_handle(char const *av, int error);
int my_ls_r(char **tab, char const *directory, int const *params);
int my_ls_t(char **tab, char const *dir, int is_file);
char **my_ls_std(char **tab, int is_file, int *error);