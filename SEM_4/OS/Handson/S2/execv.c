// program to demonstrate creation of child processes and executing commands using fork(), execl() and wait() 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    int y = 0;

    p1 = fork();

    if (p1 > 0) //parent process
    {
        wait(NULL);

        y = y - 1;

        printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);

        execl("/bin/ls", "/home/suresh/OS", NULL);
    }
    else if (p1 == 0) // child process 
    {
        p2 = fork();

        if (p2 > 0)
        {
           wait(NULL);
        }
        else if (p2 == 0)
        {
           y = y + 5;
           
           printf("This is grandchild. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

           execl("/bin/ls", "/home/suresh/OS", "-r", NULL);

           exit(0);
        }

        y = y + 1;

        printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

        char *a[] = {NULL};

        execv("/home/suresh/OS/welcome.exe", a);

        exit(0);
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}