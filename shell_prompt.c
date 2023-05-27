#include "shell.h"
/**
 * handle_command - Handle the execution of a command
 * @tokens: Array of command tokens
 */
void handle_command(char **tokens)
{
	if (_strcmp(tokens[0], "env") == 0)
		my_environ();
	else if (tokens[0][0] == '/')
	{
		if (access(tokens[0], X_OK) == 0)
		{
			execv(tokens[0], tokens);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "Error: Program '%s' not found or not executable.\n",
					tokens[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (_strcmp(tokens[0], "ls") == 0)
	{
		if (tokens[1] != NULL && _strcmp(tokens[1], "-l") == 0)
		{
			if (tokens[2] != NULL)
			{
				execv("/bin/ls", tokens);
				perror("execv");
				exit(EXIT_FAILURE);
			}
			else
			{
				execv("/bin/ls", tokens);
				perror("execv");
				exit(EXIT_FAILURE);
			}
		}
		else
			search_program("ls", getenv("PATH"), tokens);
	}
	else
		handle_unrecognized_command(tokens);
}

/**
 * process_input - Process the user input
 * @command: Input command string
 * Return: 0 or otherwise
 */
void process_input(char *command)
{
	char *tokens[MAX_TOKENS] = {NULL};
	int numwords, exit_status;

	numwords = tokenizer(command, " \t\r\n\a", tokens);
	tokens[numwords] = NULL;
	if (numwords > 0)
	{
		if (_strcmp(tokens[0], "exit") == 0)
		{
			if (tokens[1] != NULL)
			{
				exit_status = exit_shell(tokens[1]);
				exit(exit_status);
			}
			else
			{
				exit_status = exit_shell(NULL);
				exit(exit_status);
			}
		}
		else if (_strcmp(tokens[0], "setenv") == 0)
			handle_setenv(tokens);
		else if (_strcmp(tokens[0], "unsetenv") == 0)
			handle_unsetenv(tokens);
		else if (_strcmp(tokens[0], "echo") == 0)
			handle_commandtoo(tokens, numwords);
		else
			handle_command(tokens);
	}
}

/**
 * run_shell - Run the shell prompt loop
 */
void run_shell(void)
{
	char *command = NULL;
	size_t x = 0;
	ssize_t cmdline;

	while (1)
	{
		prompt(stdin);
		cmdline = get_line(&command, &x, stdin);
		if (cmdline == -1)
		{
			free(command);
			return;
		}
		process_input(command);
	}
	free(command);
	command = NULL;
}

/**
 * handle_commandtoo - handles commands with more arguments
 * @tokens: input
 * @num_tokens: number of tokens found
 */
void handle_commandtoo(char **tokens, int num_tokens)
{
	int x;

	for (x = 1; x < num_tokens; x++)
	{
		printf("%s ", tokens[x]);
	}
	printf("\n");
	return;
	execute_command_with_path(tokens[0], tokens);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: ptr to array of strings
 * Return: 0 or otherwise
 */
int main(int argc, char **argv)
{
	int x;

	if (argc > 1)
	{
		if (strcmp(argv[1], "ls") == 0)
		{
			if (argc > 2)
			{
				int num_executions = argc - 2;

				for (x = 0; x < num_executions; x++)
					search_program("ls", getenv("PATH"), argv + 2);
			}
			else
			{
				search_program("ls", getenv("PATH"), argv);
			}
		}
	}
	run_shell();
	return (0);
}
