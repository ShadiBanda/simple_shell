#include "shell.h"
/**
 * tokenizer - Tokenize a string based on delimiters
 * @str: Input string to tokenize
 * @delimiters: Delimiters used to split the string
 * @tokens: Array to store the resulting tokens
 * Return: Number of tokens found
 */
int tokenizer(char *str, const char *delimiters, char *tokens[])
{
	int numwords = 0;
	char *token = strtok(str, delimiters);

	while (token != NULL && numwords < MAX_TOKENS)
	{
		if (_strlen(token) > 0)
		{
			tokens[numwords] = token;
			numwords++;
		}
		token = strtok(NULL, delimiters);
	}
	return (numwords);
}

/**
 * free_tokens - Free the memory allocated for command tokens
 * @tokens: Array of command tokens
 */
void free_tokens(char *tokens[])
{
	int x = 0;

	while (tokens[x] != NULL)
	{
		free(tokens[x]);
		x++;
	}
}
