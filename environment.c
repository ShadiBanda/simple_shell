#include "shell.h"
/**
 * my_environ - prints the current environment
 * Return: 0 on success or 1
 */
int my_environ(void)
{
	char **env = environ;

	while (*env)
	{
		if (write(STDOUT_FILENO, *env, strlen(*env)) < 0)
		{
			return (1);
		}
		if (write(STDOUT_FILENO, "\n", 1) < 0)
		{
			return (1);
		}
		env++;
	}
	return (0);
}
