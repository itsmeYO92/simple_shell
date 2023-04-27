#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


char *get(char *line)
{
	size_t i=0;

	getline(&line, &i, stdin);

	return(line);
}


/* idon't get the EOF part yet  */


int main()
{
	char *line = NULL;
int i =4;
do{
	write(STDOUT_FILENO, "$ ", 2);
	line =	get(line);
	
	printf("%s\n", line);
	i--;
	free(line);
}while(i > 0);
	return 0;
}
