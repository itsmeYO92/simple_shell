#include "shell.h"

/**
 * shell_loop - Main loop of the shell
 *
 * Return: Nothing
*/
void shell_loop(void)
{
	char *line;
	char **args;
	char **env = NULL;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = shell_read_line();
		if (!line)
			continue;
		args = shell_split_line(line);
		args[0] = get_command(args[0]);
		if (!args[0])
		{
			perror("not found");
			continue;
		}
		status = shell_execute(args, env);

		free(line);
		free(args);
	}
}

/**
 * shell_read_line - Read a line of input from stdin
 *
 * Return: The line of input
*/
char *shell_read_line(void)
{
	char *buffer = NULL;
	size_t len = 0;

	if (getline(&buffer, &len, stdin) == -1)
	{
		if (feof(stdin))
			return (NULL);

		perror("Error reading line");
		exit(EXIT_FAILURE);
	}
	printf("buffer: %d\n",strlen(buffer));
	if (*buffer == '\n')
		return (NULL);
	return (buffer);
}

/**
 * shell_split_line - Split a line into tokens (args)
 * @line: The line to be split
 *
 * Return: An array of tokens (args)
*/
char **shell_split_line(char *line)
{
	char **args = NULL;
	char *token;
	int count = 0;

	token = strtok(line, " \n");
	while (token)
	{
		args = realloc(args, sizeof(char *) * (count + 1));
		if (!args)
		{
			perror("allocating memory");
			exit(EXIT_FAILURE);
		}
		args[count] = token;
		count++;
		token = strtok(NULL, " \n");
	}
	args = realloc(args, sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("allocating memory");
		exit(EXIT_FAILURE);
	}
	args[count] = NULL;
	return (args);
}

/**
 * shell_execute - Execute a command
 * @args: An array of arguments to the command
 * @env: An array of environment variables
 *
 * Return: 1 if successful, otherwise -1
*/
int shell_execute(char **args, char **env)
{
	pid_t pid;
	int status;
	int (*builtin_func)(char **) = NULL;

	if (args[0] == NULL)
	{
		/* empty command */
		return (1);
	}

	builtin_func = get_cmd(args[0]);
	if (builtin_func != NULL) {
		/* execute built-in command*/
		return builtin_func(args);

	pid = fork();
	if (pid == -1)
	{
		perror("failed to fork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			if (errno == ENOENT)
				printf("%s: command not found\n", args[0]);
			else
				perror("Failed to execute");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	/*	do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
				perror("Failed to exit");
			if (WIFSTOPPED(status))
				printf("Process %d stopped, waiting for signal\n", pid);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	*/}
	return (1);
}

/**
 * get_cmd - Get the function pointer for a built-in command
 * @cmd_name: The name of the command to find
 *
 * Return: The function pointer if found, NULL otherwise
 */
built_in_func get_cmd(char *cmd_name)
{
    int i;
    built_in_cmd built_in_cmds[] = {
        {"cd", cd_shell},
        /* add other built-in commands here */
        {NULL, NULL}
    };
    for (i = 0; built_in_cmds[i].cmd_name != NULL; i++)
    {
        if (strcmp(cmd_name, built_in_cmds[i].cmd_name) == 0)
        {
            return built_in_cmds[i].cmd_func;
        }
    }
    return NULL;
}

