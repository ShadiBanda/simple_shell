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
int exit_shell(char **arr)
{
	int exit_code = 0;

	if (arr && arr[1] != NULL)
	{
		if (exit_code == 0 && strcmp(arr[1], "0") != 0)
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", arr[1]);
			return (-1);
		}
		else
			exit(exit_code);
	}
	else
		exit(0);
	return (0);
}
