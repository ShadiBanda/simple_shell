# include "shell.h"

/**
 * check_executable - Checks if the given program is executable.
 * @path: The path to the program.
 * @argv: An array of command-line argument strings.
 *
 * This function is called in the child process.
 * If the program is executable, it is executed with the provided arguments.
 * If the program is not executable, an error message is printed.
 */
void check_executable(const char *path, char *argv[])
{
	if (access(path, X_OK) == 0)
	{
		execv(path, argv);
		perror("execv");
		exit(EXIT_FAILURE);
	}
}

/**
 * print_error - Prints an error message and exits.
 * @msg: The error message to print.
 *
 * This function is used to print error messages and terminate the program.
 */
void print_error(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * execute_program - Executes the given program with the provided arguments.
 * @program_path: The path to the program.
 * @argv: An array of command-line argument strings.
 */
void execute_program(const char *program_path, char *argv[])
{
	pid_t child_pid = fork();

	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		check_executable(program_path, argv);
	}
	else
	{
		int status;

		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			/* Child process exited with status 0 (success) */
			exit(EXIT_SUCCESS);
		}
	}
}

/**
 * search_program - Searches for the given program
 * in the directories specified by the PATH environment variable.
 *
 * @name: The name of the program.
 * @path_env: The value of the PATH environment variable.
 * @argv: An array of command-line
 * argument strings.
 *
 * This function searches for the program
 * in each directory specified by the PATH environment variable.
 * If the program is found, it is executed with the provided arguments.
 * If the program is not found, an error message is printed.
 */
void search_program(const char *name, const char *path_env, char *argv[])
{
	char *path_env_copy = strdup(path_env);

	if (path_env_copy == NULL)
		print_error("Memory allocation failed");

	char *path_token = strtok(path_env_copy, ":");

	while (path_token != NULL)
	{
		char *program_path = malloc(strlen(path_token) + strlen(name) + 2);

		if (program_path == NULL)
			print_error("Memory allocation failed");

		strcpy(program_path, path_token);
		strcat(program_path, "/");
		strcat(program_path, name);

		execute_program(program_path, argv);

		free(program_path);
		path_token = strtok(NULL, ":");
	}

	free(path_env_copy);
	fprintf(stderr, "Error: Program '%s' not found in PATH.\n", name);
	exit(EXIT_FAILURE);
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
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <program>\n", argv[0]);
		return (1);
	}

	const char *program_name = argv[1];
	const char *path_env = getenv("PATH");

	if (path_env == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set.\n");
		return (1);
	}

	search_program(program_name, path_env, argv + 1);

	return (0);
}

