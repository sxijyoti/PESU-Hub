#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    int res,n;
    res = mkfifo("fifo1",0777);
    printf("named pipe created\n");
    
}