#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid  = getpid();
    pid_t ppid = getppid();

    printf("pid = %d;   ppid = %d;\n", (pid_t)pid, (pid_t)ppid);

    return 0;

}
