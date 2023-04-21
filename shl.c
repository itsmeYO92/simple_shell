#include "shell.h"

/**
 * print_prompt - prints the shell prompt,
 *		 which is the current working directory
 */
void print_prompt(void)
{
	char *cwd = getcwd(NULL, 0);

	printf("%s$ ", cwd);
	free(cwd);
}

/**
 * read_input - reads input from the user
 *
 * Return: a pointer to the input string
 */
char *read_input(void)
{
	char *input = NULL;
	size_t size = 0;

	if (getline(&input, &size, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);  /* We recieved an EOF */
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}

	}

	return (input);
}

/**
 * parse_input - parses the input string into arguments
 *
 * @input: the input string to parse
 *
 * Return: a pointer to an array of arguments
 */
char **parse_input(char *input)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	input = comment(input); /*chekc if its a comment. */
		char *token = strtok(input, " \n");
		int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}

	args[i] = NULL;
	return (args);
}
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

	fprintf(stderr, "%s: command not found\n", args[0]);
	exit(EXIT_FAILURE);
}

/**
 * search_path - Searches for the command in directories specified by the PATH
 *	environment variable
 * @args: Argument list containing the command and its arguments
 */
void search_path(char **args)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	char cmd[MAX_PATH_LENGTH];

	while (dir != NULL)
	{
		snprintf(cmd, sizeof(cmd), "%s/%s", dir, args[0]);
		if (access(cmd, X_OK) == 0)
		{
			if (execve(cmd, args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}

		dir = strtok(NULL, ":");
	}
}

/**
 * execute_command - Forks a child process and executes the command in it
 * @args: Argument list containing the command and its arguments
 */
void execute_command(char **args)
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
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
/**
 * run_shell - main loop of the shell
*/

void run_shell(void)
{
	char *input;
	char **args;

	do {
		print_prompt();
		input = read_input();
		if (strcmp(input, "EOF") == 0)
			return;

		args = parse_input(input);

		if (args[0] != NULL)
		{
			if (strcmp(args[0], "cd") == 0)
			{
				change_directory(args);
			}
			else if (strcmp(args[0], "exit") == 0)
			{
				exit_shell(args);
			}
			else if (strcmp(args[0], "env") == 0)
			{
				print_env();
			}
			else if (strcmp(args[0], "setenv") == 0)
			{
				set_env(args);
			}
			else if (strcmp(args[0], "unsetenv") == 0)
			{
				unset_env(args);
			}
			else if (strcmp(args[0], "clear") == 0)
			{
				clear_terminal();
			}

			else
			{
				execute_command(args);
			}
		}

		free(input);
		free(args);
	} while (1);
}

/**
 * main - entry point.
 * Return: 0
*/
int main(void)
{
	run_shell();
	return (0);

}

