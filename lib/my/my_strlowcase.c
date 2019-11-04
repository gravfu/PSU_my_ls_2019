/*
** EPITECH PROJECT, 2019
** my_strlowcase.c
** File description:
** All upercase to lowercase
*/

char *my_strdup(char const *src);

char *my_strlowcase(char *str)
{
    char *str_cpy = my_strdup(str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str_cpy[i] = str[i] + 32;
    }
    return str_cpy;
}
