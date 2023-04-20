#include "shell.h"

/**
 * clear_terminal - Clear the terminal.
*/
void clear_terminal(void)
{
	printf("\033[H\033[2J");
}
