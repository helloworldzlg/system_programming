#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int ret;

    printf("alarm start!\n");

    ret = alarm(5);
    pause();

    printf("alarm end!\n");

    return 0;
}