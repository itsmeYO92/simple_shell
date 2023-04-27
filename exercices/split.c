#include <stdio.h>
#include <string.h>
int main()
{
	char line[] = "this is a test string";
	char *buffer;
	/* line != NULL strtok returns a pointer or NULL */
	buffer= strtok(line, " ");  
	while(buffer)
	{
		printf("%s\n", buffer);
		/* whene we want to keep spliting the same previous string we call strtok with NULL i used line */
		buffer = strtok(NULL, " ");
	}
	return (0);
}
