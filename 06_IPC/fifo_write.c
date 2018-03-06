#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIFO_SERVER    "./myfifo"

int main(int argc, char** argv)
{
    int fd;
    char w_buf[100];
    int nwrite;

    fd = open(FIFO_SERVER, O_WRONLY | O_NONBLOCK, 0);
    if (argc == 1)
    {
        printf("please send something\n");
        return 0;
    }

    strcpy(w_buf, argv[1]);

    nwrite = write(fd, w_buf, 100);
    if (nwrite == -1)
    {
        if (errno == EAGAIN)
            printf("the fifo has not been read yet. please try later\n");
    }
    else
        printf("write %s to the fifo\n", w_buf);

    return 0;
}