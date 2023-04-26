#include "shell.h"

/**
 * read_input - reads input from the user
 *
 * Return: a pointer to the input string
 */
char *read_input(int is_piped)
{
	char *line = NULL;
	ssize_t len;
	size_t bufsize = 0;

	if (!is_piped)
	{
		printf("$ ");
		len = getline(&line, &bufsize, stdin);

	}
	else
	{
		len = getline(&line, &bufsize, stdin);
		if (len == -1)
		{
			exit(EXIT_SUCCESS);
		}
		if (line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
		}
		/*printf("%s\n", line);*/
	}
	return (line);
}
/**
 * parse_input - parses the input string into arguments
 *
 * @line: the input string to parse
 *
 * Return: a pointer to an array of arguments
 */
char **parse_input(char *line)
{
	int bufsize = BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
