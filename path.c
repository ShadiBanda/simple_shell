#include "shell.h"

/**
 * print_error - Print error message and exit with a non-zero status.
 * @message: The error message to be printed.
 *
 * Description: This function prints the provided error message to stderr and
 *              exits the program with a non-zero status.
 */
void print_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/**
 * check_executable - Check if the program is executable in the given path.
 * @program_path: The full path of the program.
 * @argv: The array of command-line argument strings.
 * Description: This function checks if the specified program is executable
 *              in the given path. If it is executable, it is executed using
 *              execve. Otherwise, an error message is printed, and the program
 *              exits with a non-zero status.
 */
void check_executable(const char *program_path, char *const *argv)
{
	char **environ = NULL;

	if (access(program_path, X_OK) == 0)
	{
		execve(program_path, argv + 1, environ);
		perror("execve");
		free((void *)program_path);
		exit(1);
	}
	free((void *)program_path);
}

/**
 * search_program - Search for the executable program
 * in the directories of the PATH.
 *
 * @name: The name of the program to search for.
 * @path_env: The value of the PATH environment variable.
 * @argv: The array of command-line.
 */
void search_program(const char *name, const char *path_env, char *const *argv)
{
	char *path_env_copy = strdup(path_env);
	char *path_token = strtok(path_env_copy, ":");

	if (path_env_copy == NULL)
		print_error("Memory allocation failed");

	while (path_token != NULL)
	{
		char *program_path;
		size_t program_path_len = _strlen(path_token) + _strlen(name) + 2;

		program_path = malloc(program_path_len);
		if (program_path == NULL)
		{
			free(path_env_copy);
			print_error("Memory allocation failed");
		}

		sprintf(program_path, "%s/%s", path_token, name);
		check_executable(program_path, argv);

		free(program_path);
		path_token = strtok(NULL, ":");
	}

	free(path_env_copy);
	fprintf(stderr, "Error: Program '%s' not found in PATH.\n", name);
	exit(1);
}

/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 *
 * Return: 0 on success, otherwise 1.
 */
int main(int argc, char *argv[])
{
	const char *program_name;
	const char *path_env;

	if (argc != 2)
		print_error("Usage: program_name <file-to-exec>");

	program_name = argv[1];
	path_env = getenv("PATH");

	if (path_env == NULL)
		print_error("PATH environment variable not set");

	search_program(program_name, path_env, argv);

	return (0);
}
