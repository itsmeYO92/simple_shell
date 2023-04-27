#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	/* getppid gets the id of the process that started the program wich is the terminal in our case*/
	printf("%u\n",getppid());
	return(0);
}
