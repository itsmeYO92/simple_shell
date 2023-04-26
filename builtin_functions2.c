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
	write(STDOUT_FILENO, str, strlen(str));
	return (0);
}
/**
 * quit - exit shell.
 * @args: UNUSED
 * return: 0 SUCCESS.
 **/
int quit(char **args)
{
	UNUSED(args);
	exit(0);
}
