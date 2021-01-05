#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    char buffer[4096];
    
    int fd = open(".hello_there", O_RDWR);

    pid_t child = fork();

    if (child < 0)
    {
        perror("fork");
        exit(0);
    }
    else if (child == 0)
    {
        execve("./riddle", NULL, NULL);
    }

    sleep(1);

    ftruncate(fd,32768);

    close(fd);

    wait(NULL);
    
    return 0;
}