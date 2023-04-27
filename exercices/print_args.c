#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int ac, char **av)
{
	/* without using ac we'll check for NULL, (av is null terminated array */
	int i=0;
	while (av[i])
	{
		printf("%s\n",av[i]);
		i++;
	}
	return(0);
}
