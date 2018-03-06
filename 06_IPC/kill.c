#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int ret;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (0 == pid)
    {
        printf("child pid = %d\n", getpid());
        raise(SIGSTOP);
        exit(0);
    }
    else
    {
        printf("pid = %d\n", pid);
        printf("parent pid = %d\n", getpid());
        sleep(2);

        ret = waitpid(pid, NULL, WNOHANG);
        if (0 == ret)
        {
            ret = kill(pid, SIGKILL);
            if (0 == ret)
            {
                printf("kill %d\n", pid);
            }
            else
            {
                perror("kill");
            }
        }
    }
}