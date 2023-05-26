#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**
 * exit_shell - Exit the shell.
 * @arr: Array of command arguments.
 * Return: Integer representing the exit code or -1
 */
int exit_shell(char *arr)
{
	int exit_code = 0;

	if (arr == NULL)
		return (0);
	exit_code = atoi(arr);
	if (exit_code == 0)
	{
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, arr, strlen(arr));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		return (-1);
	}
	return (exit_code);
}
