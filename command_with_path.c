#include "shell.h"
/**
 * execute_command_with_path - Execute a command by searching for 
 * its executable in the PATH
 * @command: The command to execute
 * @args: The arguments for the command
 */
void execute_command_with_path(char *command, char **args)
{
	pid_t pid;
	int status, located;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return;
	}
	else if (pid == 0)
	{
		located = search_program(command, getenv("PATH"), args);
		if (!located)
		{
			printf("%s: command not found\n", command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do
		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("Waitpid error");
				exit(EXIT_FAILURE);
			}
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
