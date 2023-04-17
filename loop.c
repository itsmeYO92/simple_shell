#include "shell.h"

/**
 * loop - main loop of the shell
 *
 * Return: nothing
*/

void _loop(void)
{
	char *line;
	char **args;
	int status;

	while (1)
	{
		write(1, "$ ", 2);
		line = get_line();
		args = get_args(line);
	//	status = lsh_execute(args);

		free(line);
		free(args);
	}
}



char *get_line(void)
{
	char *buffer = NULL;
	ssize_t len = 0;

	if (getline(&buffer, &len, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);

		perror("Error reading line");
		exit(EXIT_FAILURE);
	}
	return (buffer);
}



char **get_args(char *line)
{
	char **args = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (!args)
	{
		perror("allocating memory");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \n");
	if (!token)
		exit(EXIT_SUCCESS);
	while (token)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	args[i] = NULL;
	return (args);
}














