#include "shell.h"

char *comment(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
	{
		if(input[i] == '#')
		{
			input[i] = '\0';

		}
		else
			input[i] = input[i];
	}
	return (input);
}
