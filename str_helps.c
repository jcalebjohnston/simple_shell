#include "shell.h"
/**
 * my_strtok - My custom strtok function.
 * @string: String to tokenize.
 * @delim: Delimiter used for tokenization.
 * @save_ptr: Pointer to where a delimiter is found.
 *
 * Return: The next token if not NULL.
 */
char *my_strtok(char *string, char *delim, char **save_ptr)
{
char *end;

if (string == NULL)
{
	string = *save_ptr;
}

if (*string == '\0')
{
	*save_ptr = string;
	return (NULL);
}

string += custom_strspn(string, delim);

if (*string == '\0')
{
	*save_ptr = string;
	return (NULL);
}

end = string + custom_strcspn(string, delim);

if (*end == '\0')
{
	*save_ptr = end;
	return (string);
}

*end = '\0';
*save_ptr = end + 1;

return (string);
}

/**
 * my_realloc - A function that reallocates a memory block for other use.
 * @ptr: Pointer to a previously allocated memory block.
 * @old_size: Size of the old memory block pointed by ptr.
 * @new_size: New size to be reallocated.
 *
 * Return: Pointer to the address of the reallocated memory block.
 */
void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
void *new_ptr;
size_t ind;

if (ptr == NULL)
{
	new_ptr = malloc(new_size);
	return (new_ptr);
}
else if (new_size == old_size)
{
	return (ptr);
}
else if (new_size == 0 && ptr != NULL)
{
	free(ptr);
	return (NULL);
}
else
{
	new_ptr = malloc(new_size);
	if (new_ptr != NULL)
	{
		for (ind = 0; ind < min(old_size, new_size); ind++)
		*((char *)new_ptr + ind) = *((char *)ptr + ind);
		free(ptr);

		return (new_ptr);
	}
	else
		return (NULL);
}
}
/**
 * handle_ctrl_c - A function that handles the signal -> CTRL-C
 * @signum: Signal value
 *
 * Return: Nothing
 */
void handle_ctrl_c(int signum)
{
if (signum == SIGINT)
{
	print_to_stdout("\n:) ");
}
}
/**
 * _atoi - A program that changes a char to int
 * @s: The string to consider
 *
 * Return: Int
 */
int _atoi(char *s)
{
size_t ints = 0;

do {
	if (*s == '-')
	{
		return (-1);
	}
	else if ((*s < '0' || *s > '9') && *s != '\0')
	{
		return (-1);
	}
	else if (*s >= '0'  && *s <= '9')
	{
		ints = (ints * 10) + (*s - '0');
	}
	else if (ints > 0)
	{
		break;
	}
} while (*s++);

return (ints);
}

/**
 * remove_comments - Removes comments from input string after '#'
 * @input: Input string to be processed
 *
 * Return: Nothing
 */
void remove_comments(char *input)
{
int idx = 0;

if (input[idx] == '#')
{
	input[idx] = '\0';
}
while (input[idx])
{
	if (input[idx] == '#' && input[idx - 1] == ' ')
	{
		break;
	}
	idx++;
}
input[idx] = '\0';
}
