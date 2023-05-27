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

/**
 * shell_unsetenv - Remove an environment variable
 * @args: Array of arguments [VARIABLE]
 * Return: 0 on success, -1 on failure
 */
int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Missing argument\n");
		return (-1);
	}
	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (-1);
	}
	return (-1);
}

/**
 * shell_setenv - Set a new environment variable or modify an existing one
 * @args: Array of arguments [VARIABLE, VALUE]
 * Return: 0 on success, -1 on failure
 */
int shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: Missing argument\n");
		return (-1);
	}
	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * handle_setenv - Handles the setenv command
 * @args: Array of arguments [VARIABLE, VALUE]
 * Return: 0 on success, -1 on failure
 */
int handle_setenv(char **args)
{
	if (args[1] == NULL )
	{
		my_environ();
		return (0);
	}
	if (args[2] == NULL)
		args[2] = "";
	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return (-1);
	}
	my_environ();
	return (0);
}

/**
 * handle_unsetenv - Handles the unsetenv command
 * @args: Array of arguments [VARIABLE]
 * Return: 0 on success, -1 on failure
 */
int handle_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Missing argument\n");
		return (-1);
	}
	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (-1);
	}
	my_environ();
	return (0);
}
