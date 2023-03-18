#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 1;

    chpid = fork();
    
    pid  = getpid();
    ppid = getppid();
    
    if (chpid < 0) {
    	printf ("Erorr");   	
    	
    } else if (chpid > 0) {
    	a = a - 2022;
    	    printf("My pid = %d, my ppid = %d. Parent process: a = %d\n", (int)pid, (int)ppid, a);
		
	} else {
    	a = a * 103;
		printf ("My pid = %d, my ppid = %d. Child process: a = %d\n", (int)pid, (int)ppid, a);
	}
	
    return 0;

}
