#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    char s[300];
    int num, fd_out, fd_in;

    mknod("/home/box/in.fifo", S_IFIFO | 0666, 0);
    mknod("/home/box/out.fifo", S_IFIFO | 0666, 0);

    
    fd_in = open("/home/box/in.fifo", O_RDONLY);
    fcntl(fd_in, F_SETFL, O_NONBLOCK);

    do {
        if ((num = read(fd_in, s, 300)) == -1)
            perror("read");
        else {
            s[num] = '\0';
            fd_out = open("/home/box/out.fifo", O_WRONLY);
            if ((num = write(fd_out, s, strlen(s))) == -1)
                perror("write");
            close(fd_out);
        }
    } while (1);

    return 0;
}
