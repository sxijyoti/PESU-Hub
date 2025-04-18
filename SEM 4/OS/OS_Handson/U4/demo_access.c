#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int fd;

   if (argc != 2)
      printf("invalid file\n");

   if (access(argv[1], R_OK) < 0)
      printf("read access error for %s\n", argv[1]);
   else
      printf("read access OK\n");

   if (access(argv[1], W_OK) < 0)
      printf("write access error for %s\n", argv[1]);
   else
      printf("write access OK\n");

   if (access(argv[1], X_OK) < 0)
      printf("exec access error for %s\n", argv[1]);
   else
      printf("exec access OK\n");

   if (fd = open(argv[1], O_RDONLY) < 0)
      printf("open error for %s\n", argv[1]);
   else
      printf("opened for reading\n");

   close(fd);
   exit(0);
}
