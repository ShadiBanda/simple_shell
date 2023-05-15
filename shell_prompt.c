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

	/* voiding th argc and argv for now */
	(void)argc; (void)argv;

	while (1)
	{
		prompt();
		cmdline = get_line(&command, &x, stdin);
		if (cmdline == -1)
		{
			printf("exiting shell...\n");
			return (-1);
		}
		free(command);
	}
	return (0);
}
