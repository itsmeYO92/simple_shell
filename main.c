#include "shell.h"
/**
	* main - entry point.
	* Return: 0
*/
int main(int ac, char **av)
{
	char *cmd = NULL;
	size_t len = 0;
	int i;

	if (!isatty(STDIN_FILENO))
	{
		if (getline(&cmd, &len, stdin) != -1)
		{
			for(i = 0; cmd[i]!= '\n'; i++)
				;
			cmd[i] = '\0'; /* remove new line char. */
			fprintf(stderr,"%s: %d: %s: not found\n", av[0], 1, cmd);
			exit(127);
		}
	}
	run_shell();
	return (0);
}
