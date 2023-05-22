#include "shell.h"
/**
 * display_error - prints error message to output
 * @message: the message to display
 */
void display_error(const char *message)
{
	 fprintf(stderr, "%s: not found\n", message);
}

/**
 * handle_unrecognized_command - Handle an unrecognized command
 * @tokens: Array of command tokens
 */
void handle_unrecognized_command(char *tokens[])
{
	if (tokens[1] != NULL && strcmp(tokens[1], "|") == 0 && tokens[2] != NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", tokens[0], tokens[2]);
	}
	else
		display_error(tokens[0]);
}
