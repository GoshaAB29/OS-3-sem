#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>


char *readfile(const char *path, size_t *sizedst);

size_t getsize(const char *file);


int main(void)
{
    size_t size = 0;
    const char filepath[] = "2_1.c";
    char *data = NULL;
    key_t key = -1;
    int shmid = -1;
    char *shmarr = NULL;

    if (NULL == (data = readfile(filepath, &size)))
    {
        perror("readfile");
        return EXIT_FAILURE;
    }
    
    if ((key = ftok(filepath, 0)) < 0)
    {
        free(data);
        perror("ftok");
        return EXIT_FAILURE;
    }

    if ((shmid = shmget(key, sizeof size + size, 0666 | IPC_CREAT)) < 0)
    {
        free(data);
        perror("shmget");
        return EXIT_FAILURE;
    }

    if ((shmarr = shmat(shmid, NULL, 0)) == (void *) -1)
    {
        free(data);
        perror("shmat");
        return EXIT_FAILURE;
    }

    *(size_t *) shmarr = size;
    memcpy(shmarr + sizeof size, data, size);

    free(data);

    if (shmdt(shmarr) < 0)
    {
        perror("shmdt");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

char *readfile(const char *path, size_t *sizedst)
{
    char *buf = NULL;
    size_t size = 0;
    int fd = -1;

    if ((NULL == path) || (NULL == sizedst))
    { return NULL; }

    if ((size = getsize(path)) == SIZE_MAX)
    { return NULL; }
    if ((buf = calloc(size, sizeof *buf)) == NULL)
    { return NULL; }
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        free(buf);
        return NULL;
    }

    if (read(fd, buf, size) != (ssize_t) size)
    {
        free(buf);
        close(fd);
        return NULL;
    }

    if (close(fd) < 0)
    {
        free(buf);
        return NULL;
    }

    *sizedst = size;
    return buf;
}

size_t getsize(const char *file)
{
    struct stat statbuf = {0};

    if (NULL == file)
    {
        return SIZE_MAX;
    }

    if(0 == stat(file, &statbuf))
    {
        return (size_t) statbuf.st_size;
    }
    else
    {
        return SIZE_MAX;
    }
}

