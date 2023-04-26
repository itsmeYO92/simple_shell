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
int _strlen(char *s);
int exit_shell(char **args);
char *_strcat(char *dest, char *src);
int set_env(char **args);
int unset_env(char **args);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
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
int get_line(char *input, int lim);
char *replace_variables(char *command, int status);
char *_strtok2(char *str, char *delim);
int search_path1(char *args);
int is_command(char *cmd);
int quit(char **args);
#endif
