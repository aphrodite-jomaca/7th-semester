#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    pid_t child;

    while(((child = fork()) != 32767) && (child !=0)) {
        continue;
    }


    if (child < 0)
    {
        perror("fork");
        exit(0);
    }
    else if (child == 0 && getpid() == 32767)
    {
        execve("./riddle", NULL, NULL);
    }

    wait(NULL);
    
    return 0;
}