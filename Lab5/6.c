#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    int fd[2] = {-1, -1};
    pid_t childpid = -1;

    if(pipe(fd) < 0)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    childpid = fork();

    if(childpid < 0)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (childpid > 0) {
        char string[] = "String for child of this proccess\n";
        close(fd[0]);
        
        if (sizeof string != write(fd[1], string, sizeof string))
        {
            perror("write");
            return EXIT_FAILURE;
        }

        close(fd[1]);
        wait(NULL);
    }
    else
    {
        close(fd[1]);

        if (-1 == dup2(fd[0], STDIN_FILENO))
        {
            perror("dup2");
            return EXIT_FAILURE;
        }
        close(fd[0]);
        
        if (-1 == execlp("cat", "cat", NULL))
        {
            perror("execlp");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
