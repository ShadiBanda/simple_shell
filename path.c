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
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
			{
				fprintf(stderr, "Program '%s' exited with non-zero status: %d\n", program_path, exit_status);
				_exit(EXIT_FAILURE);
			}
		}
		else if (WIFSIGNALED(status))
		{
			fprintf(stderr, "Program '%s' terminated by signal: %d\n", program_path, WTERMSIG(status));
			_exit(EXIT_FAILURE);
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
 * Return: 0 or 1 if found
 */
int search_program(const char *name, const char *path_env, char *argv[])
{
	char *path_env_copy = strdup(path_env);
	char *path_token;

	if (path_env_copy == NULL)
		print_error("Memory allocation failed");

	path_token = strtok(path_env_copy, ":");

	while (path_token != NULL)
	{
		char *program_path = malloc(strlen(path_token) + strlen(name) + 2);

		if (program_path == NULL)
			print_error("Memory allocation failed");

		strcpy(program_path, path_token);
		strcat(program_path, "/");
		strcat(program_path, name);
		if (access(program_path, X_OK) == 0)
		{
			execute_program(program_path, argv);
			free(program_path);
			free(path_env_copy);
			return (1);
		}

		free(program_path);
		path_token = strtok(NULL, ":");
	}
	free(path_env_copy);
	fprintf(stderr, "Error: Program '%s' not found in PATH.\n", name);
	return (0);
}
