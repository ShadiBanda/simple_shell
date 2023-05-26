#include "shell.h"
/**
 * getenvr - retrieves the value of an
 * environment
 * @name: ptr to address of name value
 * @env: ptr to environment array
 * Return: value of env on success or NULL
 */
char *getenvr(const char *name, char *env[])
{
	size_t name_length = 0;
	int x;

	if (name == NULL || env == NULL)
	{
		return (NULL);
	}
	for (x = 0; env[x] != NULL; x++)
	{
		if (strncmp(name, env[x], name_length) == 0 && env[x][name_length] == '=')
		{
			return (env[x] + name_length + 1);
		}
	}
	return (NULL);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}

	return (longi);
}


/**
 * char *_strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;
	int x = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}
	for ( ; x < l ; x++)
	{
		dest[x] = src[x];
	}
	dest[l] = '\0';
	return (dest);
}

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
