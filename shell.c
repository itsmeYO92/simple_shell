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
	size_t size = MAX_INPUT_LENGTH;
	char *input = malloc(sizeof(char) * MAX_INPUT_LENGTH);

	if (get_line(input, size) == -1)
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
	char *token;
	int i;

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	input = comment(input); /*chekc if its a comment. */
	token = _strtok(input, " \n");
	i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " \n");
	}

	args[i] = NULL;
	return (args);
}
