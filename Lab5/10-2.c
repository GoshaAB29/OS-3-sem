#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    int fd = -1;
    char fifoname[] = "aaa.fifo";
    char buf[64] = "";
    ssize_t readen = -1;

    fd = open(fifoname, O_RDONLY);
    while ((readen = read(fd, buf, sizeof buf)) > 0)
    {
        write(STDOUT_FILENO, buf, readen);
    }

    close(fd);

    return EXIT_SUCCESS;
}

