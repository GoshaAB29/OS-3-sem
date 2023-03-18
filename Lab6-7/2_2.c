#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


int main(void)
{
    size_t size = 0;
    const char filepath[] = "2_1.c";
    key_t key = -1;
    int shmid = -1;
    char *shmarr = NULL;

    if ((key = ftok(filepath, 0)) < 0)
    {
        perror("ftok");
        return EXIT_FAILURE;
    }

    if ((shmid = shmget(key, sizeof size, 0)) < 0)
    {
        perror("shmget");
        return EXIT_FAILURE;
    }

    if ((shmarr = shmat(shmid, NULL, SHM_RDONLY)) == (void *) -1)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }

    size = *(size_t *) shmarr;
    write(STDOUT_FILENO, shmarr + sizeof size, size);
    putchar('\n');

    if (shmdt(shmarr) < 0)
    {
        perror("shmdt");
        return EXIT_FAILURE;
    }

    if (shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        perror("shmctl");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

