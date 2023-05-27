#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**
 * exit_shell - Exit the shell.
 * @arg: Array of command arguments.
 * Return: Integer representing the exit code or 2.
 */
int exit_shell(char *arg)
{
	int exit_status;

	if (arg != NULL)
	{
		exit_status = atoi(arg);
		if (exit_status == 0 && strcmp(arg, "0") != 0)
		{
			fprintf(stderr, "exit: Illegal number: %s\n", arg);
			return (2);
		}
		return (exit_status);
	}
	else
		return (0);
}
