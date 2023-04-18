#include "shell.h"

/**
 *
 */


void shell_exit(void)
{
	write(STDOUT_FILENO, "exiting...\n", 11);
	exit(0);
}
int cd_shell(char* path)
{
	if (path == NULL)
	{
		if(chdir("HOME") == -1)
		{
			perror("failed cd");
			return (1);
		}
	}
	else
	{
		if(chdir(path) == -1)
		{
			perror("failed cd");
			return (1);
		}
	}
	return (0);
}
