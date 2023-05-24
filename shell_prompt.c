#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of strings containing the command-line arguments
 *
 * Return: 0 on successful execution
 */
int main(int argc, char **argv)
{
	char *command;
	size_t x = 0;
	ssize_t cmdline;
	char *tokens[MAX_TOKENS] = {NULL};
	int numwords;
	char *env[] = {NULL};
	char *cmd_path;

	if (argc > 1)
	{
		if (strcmp(argv[1], "ls") == 0)
		{
			if (argc > 2)
				list_dir(argv[2], "");
			else
				list_dir(".", "");
		}
		return (0);
	}
	while (1)
	{
		prompt();
		cmdline = get_line(&command, &x, stdin);
		if (cmdline == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}
		numwords = tokenizer(command, " \t\r\n\a", tokens);
		tokens[numwords] = NULL;
		if (numwords > 0)
		{
			cmd_path = find_cmd_path(tokens[0], env);
			if (_strcmp(tokens[0], "my_environ") == 0)
				my_environ();
			else if (_strcmp(tokens[0], "ls") == 0)
				execute_ls_command(numwords, tokens);
			else if (_strcmp(tokens[0], "exit") == 0)
				exit_shell();
			else
				execute_command(cmd_path, tokens, env);
		}
	}

	free(command);
	return (0);
}

/**
 * execute_ls_command - Executes the "ls" command
 * @numwords: The number of words/tokens
 * @tokens: The array of tokens
 */
void execute_ls_command(int numwords, char **tokens)
{
	if (numwords > 1)
		list_dir(".", tokens[1]);

	else
		list_dir(".", "");
}

/**
 * execute_command - Executes a command
 * @cmd_path: The path of the command
 * @tokens: The array of tokens
 * @env: The environment variables
 */
void execute_command(char *cmd_path, char **tokens, char **env)
{
	if (cmd_path != NULL)
		_exec_command(cmd_path, env);
	else
		handle_unrecognized_command(tokens);
}
