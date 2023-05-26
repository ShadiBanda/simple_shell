#include "shell.h"
/**
 * handle_command - Handle the execution of a command
 * @tokens: Array of command tokens
 * @env: Array of environment variables
 */
void handle_command(char **tokens)
{
	if (_strcmp(tokens[0], "my_environ") == 0)
		my_environ();
	else if (_strcmp(tokens[0], "ls") == 0)
	{
		if (tokens[1] != NULL)
			search_program("ls", getenv("PATH"), tokens + 1);
		else
		{
			if (!search_program("ls", getenv("PATH"), tokens))
				handle_unrecognized_command(tokens);
		}

	}
	else if (_strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1] != NULL)
			exit_shell(tokens);
		else
			exit_shell(NULL);
	}
	else
		handle_unrecognized_command(tokens);
}

/**
 * process_input - Process the user input
 * @command: Input command string
 * @env: Array of environment variables
 * Return: 0 or otherwise
 */
void process_input(char *command)
{
	char *tokens[MAX_TOKENS] = {NULL};
	int numwords;

	numwords = tokenizer(command, " \t\r\n\a", tokens);
	tokens[numwords] = NULL;
	if (numwords > 0)
		handle_command(tokens);
}

/**
 * run_shell - Run the shell prompt loop
 * @env: Array of environment variables
 */
void run_shell(void)
{
	char *command = NULL;
	size_t x = 0;
	ssize_t cmdline;

	while (1)
	{
		prompt();
		cmdline = get_line(&command, &x, stdin);
		if (cmdline == -1)
		{
			printf("Exiting shell...\n");
			free(command);
			return;
		}
		process_input(command);
	}
	free(command);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: ptr to array of strings
 * return: 0 or otherwise
 */
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "ls") == 0)
		{
			if (argc > 2)
			{
				if (!search_program("ls", getenv("PATH"), argv + 2))
				{
					handle_unrecognized_command(argv + 2);
				}
			}
			else
			{
				if (!search_program("ls", getenv("PATH"), argv))
					handle_unrecognized_command(argv);
			}
		}
	}
	run_shell();
	return (0);
}
