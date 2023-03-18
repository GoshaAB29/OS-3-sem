#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int     fd;
	size_t  size = 14;

    fd = open("Mfile", O_RDONLY);
    
    char input[size];
    read(fd, input, 14);   
   
    if(close(fd) < 0){
      printf("Can\'t close file\n");
    }

    printf("%s", input);

    return 0;
}
