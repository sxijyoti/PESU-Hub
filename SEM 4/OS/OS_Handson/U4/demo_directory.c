// Program to list all files and sub-directories in a directory.

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    struct dirent *dp;

    DIR *dir = opendir(argv[1]);

    if (!dir) 
    {
        printf("Unable to open the directory\n");
        return 0; 
    }

    while ((dp = readdir(dir)) != NULL)
    {
        printf("%s\n", dp->d_name);
    }

    // Close directory stream
    closedir(dir);

    return 0;
}
