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
	int num_words = 0;
	char *token = strtok(str, delimiters);

	while (token != NULL && num_words < MAX_TOKENS)
	{
		if (strlen(token) > 0)
		{
			tokens[num_words] = token;
			num_words++;
			token = strtok(NULL, delimiters);
		}
		token = strtok(NULL, delimiters);
	}
	return (num_words);
}
