#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    alarm(5);
    
    char data[1] = "";
    int fd[2] = {-1, -1};
    ssize_t pipesize = 0;
    ssize_t nwritten = -1;

    if(pipe(fd) < 0)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    while ((nwritten = write(fd[1], data, sizeof data)) == sizeof data)
    {
        pipesize += nwritten;
        printf("Size is %ld\n", pipesize);
    }
	
    return EXIT_SUCCESS;
}

