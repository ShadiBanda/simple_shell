#include "shell.h"
/**
 * display_error - prints error message to output
 * @message: the message to display
 */
void display_error(const char *message)
{
	fprintf(stderr, "Command not found: %s\n", message);
}

/**
 * handle_unrecognized_command - Handle an unrecognized command
 * @tokens: Array of command tokens
 */
void handle_unrecognized_command(char *tokens[])
{
	display_error(tokens[0]);
}
