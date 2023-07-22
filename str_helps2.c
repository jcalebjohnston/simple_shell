#include "shell.h"
/**
 * custom_strspn - Returns the length of a sub-string.
 * @main_str: Main string.
 * @sub_str: Sub-string.
 *
 * Return: Number of matched bytes.
 */
int custom_strspn(char *main_str, char *sub_str)
{
    int index = 0;
    int matched_bytes = 0;

    while (main_str[index] != '\0')
    {
        if (custom_strchr(sub_str, main_str[index]) == NULL)
            break;
        matched_bytes++;
        index++;
    }
    return (matched_bytes);
}

/**
 * custom_strcmp - Compare a string with another.
 * @s1: The first string to consider.
 * @s2: The second string to consider.
 *
 * Return: Difference of the two strings if different.
 */
int custom_strcmp(char *s1, char *s2)
{
    int index = 0;

    while (s1[index])
    {
        if (s1[index] != s2[index])
        {
            break;
        }
        index++;
    }
    return (s1[index] - s2[index]);
}

/**
 * custom_strcspn - Find what is in s1 but not in s2.
 * @s1: String to be searched.
 * @s2: String to consider.
 *
 * Return: Matched index.
 */
int custom_strcspn(char *s1, char *s2)
{
    int length = 0, index;

    for (index = 0; s1[index] != '\0'; index++)
    {
        if (custom_strchr(s2, s1[index]) != NULL)
            break;
        length++;
    }
    return (length);
}

/**
 * custom_strchr - Return the index where a character is found.
 * @s1: String to search.
 * @s2: What to be searched.
 *
 * Return: The address of where s2 is found in s1.
 */
char *custom_strchr(char *s1, char s2)
{
    int index;

    for (index = 0; s1[index] != s2 && s1[index]; index++)
    {
        ;
    }
    if (s1[index] == s2)
    {
        return (s1 + index);
    }
    else
        return (NULL);
}

/**
 * custom_strcat - Append two strings together (cat).
 * @str1: Main string.
 * @str2: String to append to the main.
 *
 * Return: A string containing contents of both strings.
 */
char *custom_strcat(char *str1, char *str2)
{
    char *cat_str = NULL;
    int length_1 = str_length(str1), length_2 = str_length(str2);

    cat_str = malloc(sizeof(*cat_str) * (length_1 + length_2 + 1));
    if (!cat_str)
    {
        return (NULL);
    }
    string_copy(str1, cat_str);
    string_copy(str2, cat_str + length_1);
    cat_str[length_1 + length_2] = '\0';

    return (cat_str);
}
