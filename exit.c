#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * exit_shell - Exit the shell.
 * @arr: Array of command arguments.
 * Return: Integer representing the exit code or -1
 */
int exit_shell(char **arr)
{
	int exit_code = 0;

	if (arr[1] == NULL)
		return (0);
	else
	{
		exit_code = atoi(arr[1]);
		if (exit_code == 0)
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, arr[1], strlen(arr[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (-1);
		}
	}
	return (exit_code);
}
