#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid, chpid;

    chpid = fork();
	
	if (chpid == -1) {
		printf ("error");
		
	} else if (chpid == 0) {
		printf("child process:\n");
		(void) execle("/bin/cat", "/bin/cat", "Zadanie7.c", 0, envp);
	
	} else {
		printf("parent process:\n");
	    (void) execle("/bin/ls", "/bin/ls", "-l", 0, envp);
	}

    printf("Error on program start\n");
    exit(-1);

    return 0;

}
