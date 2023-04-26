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
		{"quit", exit_shell},
		{"exit", quit},
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
