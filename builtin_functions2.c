#include "shell.h"

/**
 * clear_terminal - Clear the terminal.
 * @args: UNUSED
 * Return: 0
*/
int clear_terminal(char **args)
{
	char str[] = "\033[H\033[2J";

	UNUSED(args);
	write(STDOUT_FILENO, str, _strlen(str));
	return (0);
}
