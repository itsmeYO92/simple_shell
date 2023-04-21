#include "shell.h"

/**
 * is_delim - check i a char is a delimeter
 * @c: charachter to check
 * @delim: delimeters
 * Return: 1 if delim 0 if not
*/
int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}


/**
 * _strtok - tokenise a string with a delimeter
 * @str: string to split
 * @delim: delimeters
 * Return: token or NULL
*/

char *_strtok(char *str, char *delim)
{
	static char *backup;
	char *token;

	if (!str)
		str = backup;
	if (!str)
		return (NULL);

	while (1)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}

	token = str;
	while (*str != '\0')
	{
		if (is_delim(*str, delim) == 1)
		{
			*str = '\0';
			backup = str + 1;
			return (token);
		}
		str++;
	}
	backup = str;
	return (token);
}
