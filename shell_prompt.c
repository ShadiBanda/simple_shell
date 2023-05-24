#include "shell.h"
/**
 * handle_command - Handle the execution of a command
 * @tokens: Array of command tokens
 * @env: Array of environment variables
 */
void handle_command(char **tokens, char **env)
{
	char *cmd_path;

	if (_strcmp(tokens[0], "my_environ") == 0)
		my_environ();
	else if (_strcmp(tokens[0], "ls") == 0)
	{
		if (tokens[1] != NULL)
			list_dir(".", tokens[1]);
		else
			list_dir(".", "");
	}
	else if (_strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1] != NULL)
			_exiting(tokens[1]);
		else
			_exiting(NULL);
	}
	else
	{
		cmd_path = find_cmd_path(tokens[0], env);
		if (cmd_path != NULL)
			_exec_command(cmd_path, env);
		else
			handle_unrecognized_command(tokens);
	}
}

/**
 * process_input - Process the user input
 * @command: Input command string
 * @env: Array of environment variables
 * Return: 0 or otherwise
 */
void process_input(char *command, char **env)
{
	char *tokens[MAX_TOKENS] = {NULL};
	int numwords;

	numwords = tokenizer(command, " \t\r\n\a", tokens);
	tokens[numwords] = NULL;
	if (numwords > 0)
		handle_command(tokens, env);
}

/**
 * run_shell - Run the shell prompt loop
 * @env: Array of environment variables
 */
void run_shell(char **env)
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
		process_input(command, env);
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
	char *env[] = {NULL};

	if (argc > 1)
	{
		if (strcmp(argv[1], "ls") == 0)
		{
			if (argc > 2)
				list_dir(argv[2], "");
			else
				list_dir(".", "");
		}
	}
	run_shell(env);
	return (0);
}
