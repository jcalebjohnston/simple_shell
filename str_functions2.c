#include "shell.h"

/**
 * _strcmp - A function that performs comparison of two strangs.
 * @s1: The first str
 * @s2: The second str
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strlen - A program taht returns the length of a string
 * @s: The str counted
 *
 * Return: Length of str
 */
int _strlen(char *s)
{
	int ite = 0;

	if (!s)
		return (0);

	while (*s++)
		ite++;
	return (ite);
}
/**
 * _strcat - A program that concatenates two strings
 * @dest: The destination buffer
 * @src: Source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *item = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (item);
}

/**
 **_strncat - A program that concatenates two strings
 *@dest: The first string
 *@src: Second string
 *@n: Amount of bytes to be maximally used
 *Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int ite = 0;
	int t = 0;
	char *s = dest;

	while (dest[ite] != '\0')
		ite++;
	while (src[t] != '\0' && t < n)
	{
		dest[ite] = src[t];
		ite++;
		t++;
	}
	if (t < n)
		dest[ite] = '\0';
	return (s);
}

/**
 *_atoi - A program that converts a string to an integer
 *@s: The string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int t, sign = 1, flag = 0, product;
	unsigned int result = 0;

	for (t = 0;  s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sign *= -1;

		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		product = -result;
	else
		product = result;

	return (product);
}
