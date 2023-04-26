#include "shell.h"

/**
 * read_input - reads input from the user
 *
 * Return: a pointer to the input string
 */
char *read_input(int is_piped)
{
	ssize_t len;
	size_t bufsize = 0;
	char *line = NULL;

	if (!is_piped)
	{
		printf("$ ");
		fflush(stdout);
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

	char *line_cpy = strdup(line);

	free(line);
	return (line_cpy);
}
/**
 * parse_input - parses the input string into arguments
 *
 * @line: the input string to parse
 *
 * Return: a pointer to an array of arguments
 */
char **parse_input(char *line, char **tokens)
{
	int bufsize = BUFSIZE, position = 0;
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
				free(token);
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	free(token);
	tokens[position] = NULL;
	return (tokens);
}
