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
 * my_setenv - set a new environment variable or modify an existing one
 * @variable: name of the variable
 * @value: value of the variable
 * Return: 0 on success, -1 on failure
 */
int my_setenv(const char *variable, const char *value)
{
	if (!variable || !value)
	{
		fprintf(stderr, "setenv: Missing variable or value\n");
		return (-1);
	}
	if (setenv(variable, value, 1) == -1)
	{
		fprintf(stderr, "setenv: Failed to set environment variable\n");
		return (-1);
	}
	return (0);
}

/**
 * my_unsetenv - remove an environment variable
 * @variable: name of the variable to remove
 * Return: 0 on success, -1 on failure
 */
int my_unsetenv(const char *variable)
{
	if (!variable)
	{
		fprintf(stderr, "unsetenv: Missing variable\n");
		return (-1);
	}
	if (unsetenv(variable) == -1)
	{
		fprintf(stderr, "unsetenv: Failed to unset environment variable\n");
		return (-1);
	}
	return (0);
}
