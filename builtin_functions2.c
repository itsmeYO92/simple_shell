#include "shell.h"

/**
 * clear_terminal - Clear the terminal.
 * @args: UNUSED
 * Return: 0
*/
int clear_terminal(char **args)
{
	UNUSED(args);
	printf("\033[H\033[2J");
	return (0);
}
