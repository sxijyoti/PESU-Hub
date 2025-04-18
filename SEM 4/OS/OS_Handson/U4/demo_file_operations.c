// Program to demo file operations
//
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd;
	int i, err = 0;
        char buf[10] = "";

	fd = creat("/home/ubuntu/OS/temp.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1)
	   printf("unable to create file\n");

	for (i = 0; i < 10; i++)
	   write(fd, "0123456789", 10);

	close(fd);

	fd = open("/home/ubuntu/OS/temp.txt", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        err = lseek(fd, 5, SEEK_SET);

	if (err == -1)
           printf("Unable to seek\n");

	err = read(fd, buf, 5);

	if (err == -1)
		printf("read failed\n");

	printf("read: %s\n", buf);

        err = lseek(fd, -4, SEEK_END);

	if (err == -1)
           printf("Unable to seek to the EOF\n");

	memset(buf, 0, strlen(buf));
	err = read(fd, buf, 3);

	if (err == -1)
		printf("read failed\n");

	printf("read: %s\n", buf);
	close(fd);
}


