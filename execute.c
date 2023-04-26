#include "shell.h"

char *builtin_str[] = {
    "cd",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &change_directory,
    &exit_shell
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}
/**
	* execute_command - Forks a child process and executes the command in it
	* @args: Argument list containing the command and its arguments
	* Return: 0
	*/
int execute_command(char **args)
{
	int i, status;
	pid_t pid;
	int wpid;
	
	UNUSED(wpid);
	if (args[0] == NULL)
	{
		return (1);
	}

	for (i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}

	pid = fork();
	if (pid == 0)
	{
        /* Child process */
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr,"%s: command not found\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
        /* Fork error */
		perror("fork");
	}
	else
	{
        /* Parent process */
		do{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
/**
 * run_shell - run the shell.
 */
void run_shell(void)
{
	int bufsize = BUFSIZE;
	int is_piped = 0;
	int status;

    /* Check if input is coming from a pipe */
	if (!isatty(STDIN_FILENO))
	{
		is_piped = 1;
	}
	
	do{
		char *line = read_input(is_piped);
		char **args = malloc(bufsize * sizeof(char *));

		args = parse_input(line, args);
		status = execute_command(args);
		free(line);
		free(args);
	} while (status);
}
/**
 * exit_shell - exit shell
 * @args: parsed user input
 * Return: exit with custom exit code 0 per deualt or 2 on error
*/
int exit_shell(char **args)
{
	int exit_status;

	if (args[1] != NULL)
	{
		
		exit_status = atoi(args[1]);
		free(args);
		exit(exit_status);
	}
	else
	{
		free(args);
		exit(EXIT_SUCCESS);
	}
}
/**
 * change_directory - changes the current working directory
 *
 * @args: the arguments for the cd command
 * Return: 0 if successful
 */
/* Change directory */
int change_directory(char **args)
{
	char *home_dir = getenv("HOME");
	char *prev_dir = getenv("OLDPWD");

	if (args[1] == NULL)
	{
		chdir(home_dir);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (prev_dir == NULL)
		{
			fprintf(stderr, "shell: no previous directory\n");
			return (1);
		}
		chdir(prev_dir);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("shell");
		}
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(NULL, 0), 1);
	return (1);
}

