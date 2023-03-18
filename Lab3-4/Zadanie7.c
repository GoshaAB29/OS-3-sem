#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid, chpid;

    chpid = fork();
	
	switch (chpid) {
	case -1:
		printf ("error");
		break;
	
	case 0:
		printf("child process:\n");
		(void) execle("/bin/cat", "/bin/cat", "5.out", 0, envp);
		break;
	
	default:
		printf("parent process:\n");
	    (void) execle("/bin/ls", "/bin/ls", "-l", 0, envp);
	}

    printf("Error on program start\n");
    exit(-1);

    return 0;

}
