#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int fd = creat(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

   if (fd == -1)
      printf("unable to create file\n");

   for (int i = 0; i < 10; i++)
      write(fd, "0123456789", 10);

   close(fd);

   if (truncate(argv[1], 50) < 0)
      printf("unable to truncate the file\n");

   exit(0);
}
