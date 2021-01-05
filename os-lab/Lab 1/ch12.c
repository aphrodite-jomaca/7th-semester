#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char** argv){

    int fd = open(argv[1], O_WRONLY);
    lseek(fd,0x6f, SEEK_SET);
    write(fd,argv[2],sizeof(argv[2]));
    close(fd);
}