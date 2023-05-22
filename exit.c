#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * exit_shell - Exit the shell.
 * @arr: Array of command arguments.
 * Return: Integer representing the exit code.
 */
int exit_shell(char **arr)
{
	int i = 0;

	if (arr[1] == NULL)
	{
		return (0);
	}
	else
	{
		i = atoi(arr[1]);
		if (i == 0)
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, arr[1], strlen(arr[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (-1); /* Return -1 to indicate an error*/
		}
		else
		{
			return (i);
		}
	}
}
