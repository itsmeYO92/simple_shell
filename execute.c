#include "shell.h"
/**
	* child_process - Executes the command in the child process
	* @args: Argument list containing the command and its arguments
	*/
void child_process(char **args)
{
	if (access(args[0], X_OK) == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}

	search_path(args);
	write(STDERR_FILENO, args[0], strlen(args[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(EXIT_FAILURE);
}

/**
	* search_path - Searches for the command in directories specified by the PATH
	*      environment variable
	* @args: Argument list containing the command and its arguments
	*/
void search_path(char **args)
{
	char *path = getenv("PATH");
	char *dir = _strtok(path, ":");
	char *cmd = malloc(sizeof(char) * MAX_PATH_LENGTH);

	while (dir != NULL)
	{
		strcpy(cmd, dir);
		strcat(cmd, "/");
		strcat(cmd, args[0]);
		strcat(cmd, "\0");
		if (access(cmd, X_OK) == 0)
		{
			if (execve(cmd, args, NULL) == -1)
			{
				free(cmd);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}

		dir = _strtok(NULL, ":");
	}
	free(cmd);
}

/**
	* execute_command - Forks a child process and executes the command in it
	* @args: Argument list containing the command and its arguments
	* Return: 0
	*/
int execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	/* Child process */
		child_process(args);
	}
	else
	{
	/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}
/**
	* run_shell - main loop of the shell
*/

void run_shell(void)
{
	char *input;
	char **args;
	char *token;

	do {
		if (isatty(STDIN_FILENO) == 1)
			print_prompt();
		input = read_input();
		token = _strtok2(input, ";\n");
		while (token)
		{
			args = parse_input(token);

			if (args[0] != NULL)
			{
				execution_function(args)(args);
			}
			token = _strtok2(NULL, ";\n");
		}
		free(input);
		if (args)
			free(args);
	} while (1);
}
