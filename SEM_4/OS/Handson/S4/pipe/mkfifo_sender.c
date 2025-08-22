#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int res,n;
    res = open("fifo1",O_WRONLY);
    
    write(res,"message",7);
    printf("Sender process %d sent the data\n", getpid());

    return 0;
}