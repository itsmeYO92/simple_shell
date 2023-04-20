#include "shell.h"

/**
 * comment - removes the comments from an input
 * @input: input
 * Return: input without comment
*/

char *comment(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			input[i] = '\0';

		}
		else
			input[i] = input[i];
	}
	return (input);
}
