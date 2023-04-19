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

extern char **environ;

/*
 * FUNCTIONS
*/
void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
char *get_command(char *args);
int shell_execute(char **args, char **env);
int cd_shell(char* path);
char *get_command(char *args);
void (*get(char *command))(void);
int print_env(void);
#endif
