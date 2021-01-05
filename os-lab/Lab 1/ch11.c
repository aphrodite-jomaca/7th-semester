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
    
    int fd = open("tell_me", O_RDWR | O_CREAT | O_TRUNC, 0777);
    int fds = open("secret_number", O_RDWR | O_CREAT | O_TRUNC, 0600);

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

    read(fds,buffer,4096);
    write(fd,buffer,4096);

    close(fd);
    close(fds);
    wait(NULL);
    
    return 0;
}