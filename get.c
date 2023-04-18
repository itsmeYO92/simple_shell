#include "shell.h"

void (*get(char *command))(void)
{
	int i = 0;
	builtin_t builtin[] = {
		{"exit", shell_exit},
		{"", NULL}
	};

	while (strcmp(builtin[i].name, "") != 0)
	{
		if (strcmp(builtin[i].name, command) == 0)
			return (builtin[i].f);
		i++;
	}
	return (NULL);
}
