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



/*
 * FUNCTIONS
*/

void _loop(void);
char *get_line(void);
char **get_args(char *line);

#endif
