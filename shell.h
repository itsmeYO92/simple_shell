#ifndef SHELL_H
#define SHELL_H

/*
 * LIBRARIES
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


/*
 * FUNCTIONS
*/

void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args, char **env);
#endif
