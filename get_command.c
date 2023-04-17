#include "shell.h"

/**
 * get_command - return the command with its path
 * @args: arguments
 * Return: path to command or NULL if there is no command
*/

char *get_command(char *args)
{
	char *path, *constant_path, *token, *command;
	int len = strlen(args), directory_len;
	struct stat st;

	constant_path = getenv("PATH");
	path = strdup(constant_path);
	if (path)
	{
		token = strtok(path, ":");
		while (token)
		{
			directory_len = strlen(token);
			command = malloc(sizeof(char) * directory_len * len + 2);
			if (!command)
			{
				perror(args);
				exit(EXIT_FAILURE);
			}
			strcpy(command, token);
			strcat(command, "/");
			strcat(command, args);
			strcat(command, "\0");
			if (stat(command, &st) == 0)
				return (command);
			token = strtok(NULL, ":");
		}
	}

	if (stat(args, &st) == 0)
		return (args);
	return (NULL);
}
