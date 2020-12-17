#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

int main(int argc, char **argv)
{
    int tty_fd, n;
    unsigned int freq, ch;
    unsigned char in_str[65];
    struct termios config;

    if ((tty_fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        perror("Failed to open port");
        return -1;
    }

    if (!isatty(tty_fd)) //Check if the file descriptor is pointing to a TTY device or not.
        perror("Not tty");

    memset(&config, 0, sizeof(config));

    config.c_iflag = 0;
    config.c_oflag = 0;
    config.c_lflag = 0;
    config.c_cc[VMIN] = 1;                         //One input byte is enough to return from read()
    config.c_cc[VTIME] = 0;                        //Inter-character timer off
    config.c_cflag = B9600 | CS8 | CLOCAL | CREAD; //Baud 9600, 8-bit data, CLOCAL and CREAD to ensure that
                                                   //(CLOCAL) the program does not become the 'owner' of the port subject to sporatic job control and hangup signals,
                                                   //(CREAD) and also that the serial interface driver will read incoming data bytes

    if (tcsetattr(tty_fd, TCSANOW, &config) < 0)
    {
        perror("Couldn't apply settings\n");
        return 1;
    }

    /*if (tcgetattr(tty_fd, &config) < 0)
    {
        perror("tty configuration");
        return EXIT_FAILURE;
    }*/

    if (tcflush(tty_fd, TCIOFLUSH) < 0)
    {
        perror("Cannot flush");
        return -1;
    } //Clear pseudoterminal for any garbage left

    printf("Please give a string to send to host:\n");

    if ((n = read(STDIN_FILENO, &in_str, sizeof(in_str))) > 65) //Read from stdin the input string
    {
        perror("String must be up to 64 chars long. Please, try again!\n");
        return -1;
    }

    if (write(tty_fd, &in_str, n) < n) //Write the given string to the serial port
    {
        perror("Failed to write port.\n");
        return -1;
    }

    //Wait until all data previously written to the serial line have been sent
    if (tcdrain(tty_fd) < 0)
    {
        perror("tcdrain");
        return -1;
    }

    //tcflush(tty_fd, TCIOFLUSH);

    while (read(tty_fd, &ch, 1) < 1)
        ; //Read char with max occurances
    while (read(tty_fd, &freq, 1) < 1)
        ; //Read number of occuracnes

    //Print results to hosts stdout
    printf("The most frequent character is \"%c\" and it appeared %d times\n", (char)ch, freq);



    close(tty_fd); //Close the opened device
    return 0;
}