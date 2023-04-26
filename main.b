#include "shell.h"
/**
	* main - entry point.
	* @ac: argument counter.
	* @av: arguments
	* Return: 0
*/
/* Main function */
int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);
    /* Run command loop */
	run_shell();
	return (EXIT_SUCCESS);
}
