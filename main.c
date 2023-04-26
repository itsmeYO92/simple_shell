#include "shell.h"
/**
	* main - entry point.
	* @ac: argument counter.
	* @av: arguments
	* Return: 0
*/
int main(int ac, char **av)
{
	char *cmd = NULL;
	size_t len = 0;
	int i;

	UNUSED(ac);
	if (!isatty(STDIN_FILENO))
	{
		if (getline(&cmd, &len, stdin) != -1)
		{
			for (i = 0; cmd[i] != '\n'; i++)
				;
			cmd[i] = '\0'; /* remove new line char. */
			if (execvp(cmd, av) == -1 && execve(cmd, av, environ) == -1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n", av[0], 1, cmd);
				exit(127);
			}
		}
	}
	run_shell();
	return (0);
}
