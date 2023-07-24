#include "shell.h"
/**
 * _getline - A function that reads a line from standard input
 *
 * Return: On success, returns a pointer to the read line.
 * On failure or when there's nothing more to read, return NULL.
 */
char *_getline(void)
{
static char buffer[READ_SIZE];
static ssize_t buffer_pos, bytes_read;

char *line = NULL;
ssize_t line_size = 0, t = 0;
ssize_t line_len = t - buffer_pos;
ssize_t new_line_size = line_size + line_len + 1;

while (1)
{
	if (buffer_pos >= bytes_read)
	{
		bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);
		if (bytes_read <= 0)
			return (line);
		buffer_pos = 0;
	}
	for (t = buffer_pos; t < bytes_read; t++)
	{
		if (buffer[t] == '\n')
			break;
	}
	line = my_realloc(line, line_size, new_line_size);
	if (line == NULL)
		return (NULL);
	for (t = 0; buffer_pos < bytes_read && buffer[buffer_pos] != '\n'; t++)
	{
		line[line_size + t] = buffer[buffer_pos];
		buffer_pos++;
	}
	line[line_size + t] = '\0';
	line_size = new_line_size;

	if (buffer_pos < bytes_read || line_len > 0)
		return (line);
}
}
