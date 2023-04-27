#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	int status;
	size_t iptr=0;
	pid_t child;
	char *command = NULL;
	char *av[] = {command, NULL};
	while(1)
	{
		printf("$ ");
		getline(&command, &iptr, stdin);
		command = strtok(command, "\n");
		//run new procces and wait for it to execut
		child = fork();
		if (child == -1)
			return (1);
		if (child == 0)
			execve(av[0], av, NULL);
		else
			wait(&status);
		//run command inside child 
	}

	free(command);
	
	return 0;
}
