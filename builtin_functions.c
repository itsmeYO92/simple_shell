#include "shell.h"


/**
 * print_env - set a variable in the environ
 * @args: UNUSED
 * Return: 0 if successful
*/

int print_env(char **args)
{
	char **env = environ;

	UNUSED(args);

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return (0);
}
/**
 * set_env - set a variable in the environ
 * @args: parsed user input
 * Return: 0 if successful
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
 * unset_env - unset a variable in environ
 * @args: parsed user input
 * Return: 0 if successful
*/
int unset_env(char **args)
{
	if (!args[1] || args[2])
	{
		printf("Usage:\n\tunsetenv VARIABLE\n");
		return (1);
	}
	if (unsetenv(args[1]) == -1)
	{
		perror(args[0]);
		return (1);
	}
	return (0);
}
/**
 * exit_shell - exit shell
 * @args: parsed user input
 * Return: exit with custom exit code 0 per deualt or 2 on error
*/

int exit_shell(char **args)
{
	int EXIT_CODE;
	char *checker;

	if (args[2])
	{
		printf("bash: exit: too many arguments\n");
		exit(2);
	}
	if (!args[1])
		exit(0);
	EXIT_CODE = strtol(args[1], &checker, 10);
	if (EXIT_CODE < 0)
		EXIT_CODE += 256;
	if (*checker != '\0')
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}

	exit(EXIT_CODE % 256);

}
/**
 * change_directory - changes the current working directory
 *
 * @args: the arguments for the cd command
 * Return: 0 if successful
 */
int change_directory(char **args)
{
	char *OLD = getenv("OLDPWD");
	char *PWD = getenv("PWD");

	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return (1);
		}
		setenv("OLDPWD", PWD, 1);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (chdir(OLD) != 0)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		setenv("OLDPWD", PWD, 1);
		printf("%s\n", OLD);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
			return (1);
		}
		setenv("OLDPWD", PWD, 1);
	}
	return (0);
}

