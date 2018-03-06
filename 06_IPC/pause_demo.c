#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int ret;

    printf("sleep start!\n");

    ret = sleep(5);

    printf("sleep end!\n");

    pause();

    return 0;
}