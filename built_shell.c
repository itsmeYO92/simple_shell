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



int print_env(void)
{
	char **env = environ;
	
	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return (0);
}
