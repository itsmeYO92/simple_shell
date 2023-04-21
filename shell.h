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
	int (*f)(char **args);
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
#define MAX_PATH_LENGTH 512
#define UNUSED(x) (void)(x)

/*
 * FUNCTIONS
*/

void print_prompt(void);
char *read_input(void);
int execute_command(char **args);
char **parse_input(char *input);
int change_directory(char **args);
void run_shell(void);
int exit_shell(char **args);
int set_env(char **args);
int unset_env(char **args);
int clear_terminal(char **args);
int print_env(char **args);
char *comment(char *input);
void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
char *get_command(char *args);
int shell_execute(char **args, char **env);
int cd_shell(char *path);
void child_process(char **args);
void search_path(char **args);
char *_strtok(char *str, char *delim);
int is_delim(char c, char *str);
int (*execution_function(char **args))(char **fargs);
#endif
