#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    int fd = -1;
    char fifoname[] = "aaa.fifo";
    char info[] = "2+3=5!";

    if (mknod(fifoname, S_IFIFO | 0666, 0) < 0)
    {
        perror("mknod");
        return EXIT_FAILURE;
    }

    fd = open(fifoname, O_WRONLY);
    while (write(fd, info, sizeof info) != sizeof info) {}

    close(fd);

    return EXIT_SUCCESS;
}

