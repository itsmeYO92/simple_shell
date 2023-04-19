#include "shell.h"
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
void print_prompt(void);
char *read_input(void);
void execute_command(char **args);
char **parse_input(char *input);
void change_directory(char **args);
void run_shell(void);
void exit_shell(void);
int set_env(char **args);


/**
 *
*/
int set_env(char **args)
{
	if (!args[2] || args[3])
	{
		printf("Usage:\n\tsetenv VARIABLE VALUE\n");
		return (1);
	}
	if (setenv(args[1], args[2], 1) == -1)
	{
		perror(args[0]);
		return (1);
	}
	return (0);
}


/**
 * print_prompt - prints the shell prompt, which is the current working directory
 */
void print_prompt(void)
{
    char *cwd = getcwd(NULL, 0);
    printf("%s> ", cwd);
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

    if (getline(&input, &size, stdin) == -1) {
	if (feof(stdin))
	{
		write(STDOUT_FILENO, "\n", 1);
		return ("EOF");
	}
        perror("getline");
        exit(EXIT_FAILURE);
    }

    return input;
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
    if (args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(input, " \n");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }

    args[i] = NULL;
    return args;
}

/**
 * execute_command - executes a command with the given arguments
 *
 * @args: the arguments for the command
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        if (args[0][0] == '/') {
            // Absolute path

            if (access(args[0], X_OK) == 0) {
                if (execve(args[0], args, NULL) == -1) {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "%s: command not found\n", args[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            // Relative or command in PATH

            char *path = getenv("PATH");
            char *dir = strtok(path, ":");
            char cmd[512];

            while (dir != NULL) {
                snprintf(cmd, sizeof(cmd), "%s/%s", dir, args[0]);

                if (access(cmd, X_OK) == 0) {
                    if (execve(cmd, args, NULL) == -1) {
                        perror("execve");
                        exit(EXIT_FAILURE);
                    }
                }

                dir = strtok(NULL, ":");
            }

            fprintf(stderr, "%s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process

        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/**
 * change_directory - changes the current working directory
 *
 * @args: the arguments for the cd command
 */
void change_directory(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
		}
	}
}

void exit_shell(void)
{
	exit(0);
}

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

        if (args[0] != NULL) {
            if (strcmp(args[0], "cd") == 0) {
                change_directory(args);
            } else if (strcmp(args[0], "exit") == 0) {
                exit_shell();
            } else if (strcmp(args[0], "env") == 0) {
                print_env();
            } else if (strcmp(args[0], "setenv") == 0) {
                set_env(args);
            } else {
                execute_command(args);
            }
        }

        free(input);
        free(args);
    } while (1);
}
int main()
{
	run_shell();
	return 0;

}

