#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIFO_SERVER    "./myfifo"

int main()
{
    char buf_r[100];
    int fd;
    int nread;
    int ret;

    ret = mkfifo(FIFO_SERVER, O_CREAT | O_EXCL);
    if ((ret < 0) && (errno != EEXIST))
        printf("cannot create fifoserver\n");

    printf("prepareing for reading bytes...\n");

    memset(buf_r, 0, sizeof(buf_r));

    fd = open(FIFO_SERVER, O_RDONLY | O_NONBLOCK, 0);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    while (1)
    {
        memset(buf_r, 0, sizeof(buf_r));

        nread = read(fd, buf_r, 100);
        if (nread == -1)
        {
            if (errno == EAGAIN)
                printf("no data yet\n");
        }
        printf("read %s from FIFO_SERVER\n", buf_r);
        sleep(1);
    }

    pause();
    unlink(FIFO_SERVER);
}