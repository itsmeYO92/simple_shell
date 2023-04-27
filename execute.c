#include "shell.h"

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	write(1, "\n", 1);
	fflush(stdin);
}

/**
	* execute_command - Forks a child process and executes the command in it
	* @args: Argument list containing the command and its arguments
	* Return: 0
	*/
int execute_command(char **args, char *line)
{
	int i = 0, status;
	pid_t pid;
	int wpid;
	builtin_t builtin[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", change_directory},
		{NULL, NULL}
	};
	
	UNUSED(wpid);
	if (args[0] == NULL)
	{
		return (1);
	}

	while (builtin[i].name)
	{
		if (strcmp(args[0], builtin[i].name) == 0)
		{
			(builtin[i].f)(args, line);
			return (1);
		}
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
        /* Child process */
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr,"%s: command not found\n", args[0]);
			free(args);
			free(line);
		}
		exit(126);
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
	char *line = NULL;

    /* Check if input is coming from a pipe */
	if (!isatty(STDIN_FILENO))
	{
		is_piped = 1;
	}
	
	do{
		char **args = malloc(bufsize * sizeof(char *));
		line = read_input(is_piped, line, args); 
		args = parse_input(line, args);
		status = execute_command(args, line);
		
		free(args);
		free(line);
	} while (status);
}
