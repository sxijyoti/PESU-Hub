// Write a program to create a child process that lists all the executing user processes. 
//(Avoid creation of zombie process)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p1 = fork();
    // Parent process
    if (p1 > 0) { 
        // to avoid zombie process
        wait(NULL); 
        printf("Parent Process with id : %d execution is resumed.\n", getpid());

    } else if (p1 == 0) { // Child process

        char *user = getenv("USER");

        if (user == NULL) {
            printf("Error finding user environment .\n");
            exit(0);
        }

        printf("Child Process with id : %d executing 'ps -u' command.\n", getpid());
        printf("Listing all the executing user processes:\n");


        if(execlp("ps", "ps", "-u", user , NULL) == -1){
            printf("Error executing the 'ps -u' command. \n");
            exit(0);
        }

    } else { // fork failure
        printf("Error creating fork. Resuming parent process execution without child process creation.\n");
        exit(0);
    }
    
    return 0;

}


