#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	/* the command we want to use */
	char *av[] = {"/bin/ls", NULL};
	/* status is used with wait and only god understands how this works*/
	int status;
	pid_t child;

	for (int i = 0; i < 5; i++)
	{
		/* we creat new process*/
		child = fork();
		if (child == -1)
			return (1);
		/* if child == 0 means we are in the new created process (the child) */
		if (child == 0)
			/*we execute the command in child */
			execve(av[0], av, NULL);
		else
		{
			/* wait for the child to finish before we start new process*/
			wait(&status);
			printf("child %u executed\n",child);
		}	
	}
	return (0);
			
}
