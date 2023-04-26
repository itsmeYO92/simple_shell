#include "shell.h"

/**
 * execution_function - control which function should be executed
 * @args: arguments
 * Return: function to execute
*/
int (*execution_function(char **args))(char **fargs)
{
	int i = 0;
	builtin_t builtin[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", change_directory},
		{"clear", clear_terminal},
		{NULL, NULL}
	};
	while (builtin[i].name)
	{
		if (_strcmp(builtin[i].name, args[0]) == 0)
			return (builtin[i].f);
		i++;
	}
	return (execute_command);
}

int search_path1(char *args)
{
	char *path = getenv("PATH");
	char *dir = _strtok(path, ":");
	char *cmd = malloc(sizeof(char) * MAX_PATH_LENGTH);

	while (dir != NULL)
	{
		_strcpy(cmd, dir);
		_strcat(cmd, "/");
		_strcat(cmd, args);
		_strcat(cmd, "\0");
		if (access(cmd, X_OK) == 0)
		{
			return (1);
		}

		dir = _strtok(NULL, ":");
	}
	free(cmd);
	return (0);
}

int is_command(char *cmd)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", change_directory},
		{"clear", clear_terminal},
		{NULL, NULL}
	};
	while (builtin[i].name)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			return (1);
		i++;
	}

	if ((access(cmd, X_OK) == 0) || (search_path1(cmd) != 0))
		return (1);
	return (0);
}
