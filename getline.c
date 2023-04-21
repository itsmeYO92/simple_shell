#include "shell.h"
/**
* get_line - Give the length of a line of char.
*
* @input: The Input.
* @lim: Maximum that can Read.
* Return: An integer.
*/


int get_line(char *input, int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		input[i] = c;
	}
	if (c == '\n')
	{
		input[i] = c;
		i++;
	}

	input[i] = '\0';

	if (c == EOF)
	{
		return (-1);
	}
	return (i);
}

