#include "shell.h"
#include <stdbool.h>
/**
 * read_buf - Read data into the buffer
 * @buf: The buffer to read data into
 * @buf_index: The current index in the buffer
 * @buf_size: The size of the buffer
 * @stream: The input stream to read from
 * Return: buffer size
 */
ssize_t read_buf(char *buf, size_t *buf_index, size_t *buf_size, FILE *stream)
{
	if (*buf_index >= *buf_size)
	{
		*buf_size = read(fileno(stream), buf, BUFFER_SIZE);
		if (*buf_size == 0)
			return (-1);
		*buf_index = 0;
	}
	return (*buf_size);
}

/**
 * realloc_line - Reallocate memory for the line
 * @line: Pointer to the line to be reallocated
 * @n: Pointer to the allocated size
 * Return: 0 on success, -1 on failure
 */
int realloc_line(char **line, size_t *n)
{
	char *temp;

	*n *= 2;
	temp = realloc(*line, *n * sizeof(char));
	if (temp == NULL)
	{
		*line = temp;
		return (-1);
	}
	*line = temp;
	return (0);
}

/**
 * prompt - prints the shell prompt for the user
 * @stream: ptr to user input stream
 */
void prompt(FILE *stream)
{
	if (isatty(fileno(stream)))
	{
		printf("$ ");
		fflush(stdout);
	}
}

/**
 * get_line - reads a line of input
 * @line: pointer to store the address
 * @n: stores the allocated size
 * @stream: input stream to get the data from
 * Return: length or otherwise
 */
ssize_t get_line(char **line, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index;
	static size_t buffer_size;
	ssize_t read_chars = 0;
	size_t length = 0;
	int x;

	if (line == NULL || n == NULL)
		return (-1);
	if (*line == NULL || *n == 0)
	{
		*n = 128;
		*line = malloc(*n * sizeof(char));
		if (*line == NULL)
			return (-1);
	}
	while (1)
	{
		read_chars = read_buf(buffer, &buffer_index, &buffer_size, stream);
		if (read_chars == -1)
			return (-1);
		if (read_chars == 0)
			break;
		x = buffer[buffer_index++];
		(*line)[length++] = x;
		if (length >= *n - 1)
		{
			if (realloc_line(line, n) == -1)
				return (-1);
		}
		if (x == '\n')
			break;
	}
	if (length == 0 && read_chars == 0)
		return (-1);
	(*line)[length] = '\0';
	if ((*line)[length - 1] == '\n')
		(*line)[length - 1] = '\0';
	return (length);
}
