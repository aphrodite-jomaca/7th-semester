#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    int fd = open("foo5.txt", O_CREAT|O_RDWR);

    dup2(fd,99);

    execve("./riddle",NULL,NULL);

    close(fd);

    return 0;
}