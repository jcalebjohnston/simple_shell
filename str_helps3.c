#include "shell.h"

/**
 * str_length - Gets the length of a string.
 *
 * @str: The string to be considered.
 *
 * Return: The string length.
 */
int str_length(char *str)
{
	int str_len;

	if (str == NULL)
	{
		return (0);
	}
	str_len = 0;
	while (str[str_len])
	{
		str_len++;
	}

	return (str_len);
}

/**
 * remove_newline - A funct taht removes the new line as a result of enter.
 * @str: String to remove newline from.
 *
 * Return: Nothing.
 */
void remove_newline(char *str)
{
	int index = 0;

	while (str[index])
	{
		if (str[index] == '\n')
		break;
		index++;
	}
	str[index] = '\0';
}

/**
 * tokenize_string - A program that tokenizes cmd_st
 * r and saves as an array of strings.
 *
 * @cmd: String to be tokenized.
 * @delim: What to tokenize with.
 *
 * Return: Array of strings containing commands.
 */
char **tokenize_string(char *cmd, char *delim)
{
	int num = 0;
	char **tokens_array = NULL, *token = NULL, *ptr = NULL;

	token = my_strtok(cmd, delim, &ptr);

	while (token != NULL)
	{
		tokens_array = my_realloc(tokens_array, sizeof(*tokens_array
				) * num, sizeof(*tokens_array) * (num + 1));
		tokens_array[num] = token;
		token = my_strtok(NULL, delim, &ptr);
		num++;
	}

	tokens_array = my_realloc(tokens_array, sizeof(*tokens_array
			) * num, sizeof(*tokens_array) * (num + 1));
	tokens_array[num] = NULL;

	return (tokens_array);
}

/**
 * string_copy - A funct taht copies a string to a new address.
 *
 * @src: Where to copy from.
 * @dest: Where to copy to.
 *
 * Return: Nothing.
 */
void string_copy(char *src, char *dest)
{
	int index;

	for (index = 0; src[index]; index++)
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';
}

/**
 * print_to_stdout - Helper function to print to standard output.
 *
 * @str: What to be printed.
 *
 * Return: Return nothing.
 */
void print_to_stdout(char *str)
{
	int index;

	for (index = 0; str[index]; index++)
	{
		write(STDOUT_FILENO, &str[index], 1);
	}
}

