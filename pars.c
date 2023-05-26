#include "shell.h"
/**
 * command_check - Check if a command exists in the list of supported commands
 * @command: The command to check
 * Return: 1 if the command exists, 0 otherwise
 */
int command_check(const char *command)
{
	static const char *const command_list[] = {
		"ls",
		"echo",
		"cd",
		"exit",
		"my_environ",
		"unset_environ",
		"set_environ"
	};
	size_t num_commands = sizeof(command_list) / sizeof(command_list[0]);
	size_t n;

	for (n = 0; n < num_commands; n++)
	{
		if (strcmp(command, command_list[n]) == 0)
			return (1);
	}
	return (0);
}
