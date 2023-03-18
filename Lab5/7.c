#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd_1[2] = {-1, -1};
    int fd_2[2] = {-1, -1};
    pid_t child = -1;
    char resstring[64] = "";

    if(pipe(fd_1) < 0)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    if(pipe(fd_2) < 0)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    child = fork();

    if (child < 0)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (child != 0)
    {
        size_t size = 0;
        close(fd_1[0]);
        close(fd_2[1]);

        size = write(fd_1[1], "Hello!", 7);
        size = read(fd_2[0], resstring, sizeof resstring);

        if (size != 14)
        {
            perror("Can\'t write all string to pipe\n");
            return EXIT_FAILURE;
        }

        close(fd_1[1]);
        close(fd_2[0]);
        printf("Parent exit, resstring: %s\n", resstring);
    }
    else
    {
        ssize_t size = -1;
        close(fd_1[1]);
        close(fd_2[0]);

        size = write(fd_2[1], "Hello!!!", 9);
        size = read(fd_1[0], resstring, sizeof resstring);

        if (size < 0)
        {
            perror("read");
            return EXIT_FAILURE;
        }

        printf("Child exit, resstring: %s\n", resstring);

        close(fd_1[0]);
        close(fd_2[1]);
   }

   return 0;
}
