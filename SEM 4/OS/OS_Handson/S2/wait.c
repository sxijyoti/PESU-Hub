// program to demonstrate fork() and wait() 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1;

    int y = 0;

    p1 = fork();

    if (p1 > 0) //parent process
    {
        wait(NULL);

        y = y - 1;

        printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);
    }
    else if (p1 == 0) // child process 
    {
        y = y + 1;

        printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

        exit(0);
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}