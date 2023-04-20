#ifndef SHELL_H
#define SHELL_H

/*
 * STRUCTURES
 */
/**
 * struct builtin - Struct format
 *
 * @name: name of the builin
 * @f: The function associated
 */
typedef struct builtin
{
	char *name;
	void (*f)(void);
} builtin_t;
/*
 * LIBRARIES
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
/*
 * MACROS
*/

extern char **environ;
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64



/*
 * FUNCTIONS
*/

void print_prompt(void);
char *read_input(void);
void execute_command(char **args);
char **parse_input(char *input);
void change_directory(char **args);
void run_shell(void);
int exit_shell(char **args);
int set_env(char **args);
int unset_env(char **args);
void clear_terminal(void);
int print_env(void);
char *comment(char *input);
void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
char *get_command(char *args);
int shell_execute(char **args, char **env);
int cd_shell(char *path);

#endif
