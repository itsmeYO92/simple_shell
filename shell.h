#ifndef SHELL_H
#define SHELL_H

/* Function declarations */
void run_shell(void);
void sigintHandler(__attribute__((unused))int sig_num);
char *read_input(int is_piped, char *line, char **args);
char **parse_input(char *line, char **tokens);
int execute_command(char **args, char *line);
int change_directory(char **args, char *line);
int exit_shell(char **args, char *line);
int num_builtins(void);
int _isdigit(int c);
int set_env(char **args, char *line);
int unset_env(char **args, char *line);
int print_env(char **args, char *line);
char *comment(char *input);
/*
 * LIBRARIES
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
/*
 * MACROS
*/

extern char **environ;
#define UNUSED(x) (void)(x)
#define BUFSIZE 1024
#define TOKEN_DELIM " \t\r\n\a"
/**
 * struct builtin - Struct format
 *
 * @name: name of the builin
 * @f: The function associated
 */
typedef struct builtin
{
	char *name;
	int (*f)(char **args, char *line);
} builtin_t;
#endif
