#include "shell.h"

static char buffer[READ_SIZE];

ssize_t read_data_from_buffer(char *line, ssize_t *bytes_read, size_t *n);
ssize_t fill_buffer(void);
/**
 * _getline - ...
 * @lineptr: ...
 * @n: ...
 * @stream: ...
 *
 * Return: ....
 */

ssize_t _getline(char **lineptr, size_t *n)
{
	static size_t buffer_pos;
	static size_t buffer_size;
	ssize_t total_bytes_read = 0;
	ssize_t bytes_read = 0;
	char *line = NULL;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = READ_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	line = *lineptr;
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = fill_buffer();
			if (buffer_size <= 0)
			{
			break;
			}
			buffer_pos = 0;
		}
		bytes_read = read_data_from_buffer(line, &bytes_read, n);
		total_bytes_read += bytes_read;
		if (line[bytes_read - 1] == '\n')
		{
			line[bytes_read] = '\0';
			return (total_bytes_read);
		}
	}
	if (bytes_read > 0)
	return (total_bytes_read);
	return (-1);
}

/**
 * fill_buffer - A  prog taht fills the buffer with data from the stream.
 *
 * Return: Number of bytes read 4rm the stream.
 */
ssize_t fill_buffer(void)
{
	static char buffer[READ_SIZE];
	ssize_t bytes_read = read(fileno(stdin), buffer, READ_SIZE);

	return (bytes_read);
}

/**
 * read_data_from_buffer - A program that reads data from the buff to the line
 * @line: The destination buffer to store the line.
 * @bytes_read: Pointer to the number of bytes read so far.
 * @n: Pointer to the size of the line buffer.
 *
 * Return: Number of bytes read, 0 if no newlin found, -1 on er or end of fi
 */
ssize_t read_data_from_buffer(char *line, ssize_t *bytes_read, size_t *n)
{
	static size_t buffer_pos = 0;
	static size_t buffer_size = 0;
	ssize_t bytes_copied = 0;

	while (buffer_pos < buffer_size)
	{
		line[*bytes_read] = buffer[buffer_pos];
		(*bytes_read)++;
		buffer_pos++;
		bytes_copied++;

		if ((size_t)(*bytes_read) >= *n)
		{
			*n += READ_SIZE;
			line = (char *)my_realloc(line, *n - READ_SIZE, *n);
			if (line == NULL)
			{
				return (-1);
			}
		}
		if (line[*bytes_read - 1] == '\n')
		{
			line[*bytes_read] = '\0';
			return (*bytes_read);
		}
	}

	return (bytes_copied);
}
