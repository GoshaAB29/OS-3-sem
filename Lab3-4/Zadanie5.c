#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{

    (void) execle("/bin/ls", "/bin/ls", ".", 0, envp);

    printf("Error\n");
    exit(-1);

    return 0;
}

