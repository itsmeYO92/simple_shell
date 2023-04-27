#include "shell.h"
/**
	* main - entry point.
	* @ac: argument counter.
	* @av: arguments
	* Return: 0
*/
/* Main function */
int main(int ac, char **av)
{
	UNUSED(ac);
	UNUSED(av);
    /* Run command loop */
	run_shell();
	return (EXIT_SUCCESS);
}
