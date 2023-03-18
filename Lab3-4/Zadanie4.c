#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[])
{
	printf("argc = %d\n", argc);
   
	for (int i = 0; i < argc + 1; i++)
   		printf ("argv[%d] = %s\n", i, argv[i]);
   		
	int i = 0;
   
	while (envp[i] != NULL) {
   		printf ("envp[%d] = %s\n", i, envp[i]);
   		i++;
	}
   
	return 0;
}
