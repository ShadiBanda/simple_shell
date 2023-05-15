#include "shell.h"
/**
 * main - entry point
 * argc: argument count
 * argv: ptr to array of strings
 * return: 0 or otherwise
 */
int main(int argc, char **argv)
{
	char *command;
	size_t x = 0;
	ssize_t cmdline;
	char *tokens[MAX_TOKENS];
	int numwords;

	/* void for now */
	(void)argv;

	if (argc > 1)
	{
		return (0);
	}
	while (1)
	{
		prompt();
		cmdline = get_line(&command, &x, stdin);
		if (cmdline == -1)
		{
			printf("exiting shell...\n");
			return (-1);
		}
		numwords = tokenizer(command, " \t\r\n\a", tokens);
		if (numwords > 0)
		{
			if (strcmp(tokens[0], "my_environ") == 0)
				my_environ();
			else
			{
				handle_unrecognized_command(tokens);
			}
		}
		free(command);
	}
	return (0);
}
