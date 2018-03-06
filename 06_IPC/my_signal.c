#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_func(int sign_no)
{
    if (SIGINT == sign_no)
        printf("I have get SIGINT\n");
    else if (SIGQUIT == sign_no)
        printf("I have get SIGQUIT\n");
}

int main()
{
    printf("Waiting for signal SIGINT or SIGQUIT\n");

    signal(SIGINT, my_func);
    signal(SIGQUIT, my_func);

    pause();
    exit(0);
}