#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_FD        (0)
#define WRITE_FD       (1)

int main()
{
    int pipe_fd[2];
    pid_t pid;
    char buff_r[100];
    char* p_wbuf;
    int r_num;
    int ret;

    memset(buff_r, 0, sizeof(buff_r));

    ret = pipe(pipe_fd);
    if (ret < 0)
    {
        printf("pipe create error\n");
        return -1;
    }

    pid = fork();

    /* son process */
    if (pid == 0)
    {
        printf("\n");

        close(pipe_fd[WRITE_FD]);
        sleep(2);

        r_num = read(pipe_fd[READ_FD], buff_r, 100);
        if (r_num > 0)
        {
            printf("%d numbers read from the pipe: %s\n", r_num, buff_r);
        }

        close(pipe_fd[READ_FD]);
        exit(0);
    }
    else if (pid > 0) /* parent process */
    {
        close(pipe_fd[READ_FD]);

        ret = write(pipe_fd[WRITE_FD], "Hello", 5);
        if (ret > 0)
            printf("parent write 1 success\n");

        ret = write(pipe_fd[WRITE_FD], "Pipe", 5);
        if (ret > 0)
            printf("parent write 2 success\n");

        sleep(3);

        close(pipe_fd[WRITE_FD]);
        exit(0);
    }
}