// Write a C Program to check the status of the given file using system calls

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_file_perm(mode_t mode);
void print_file_type(mode_t mode);

int main() {
    const char *filename = "another_file.txt"; // file name
    struct stat file_stat;
    
    // stat() to get file info
    if (stat(filename, &file_stat) == -1) {
        perror("Error accessing file");
        return EXIT_FAILURE;
    }
    
    // if file exists and retrieved successfully
    printf("File: %s\n", filename);
    
    // type and permissions
    printf("File type: ");
    print_file_type(file_stat.st_mode);
    printf("File permissions: ");
    print_file_perm(file_stat.st_mode);
    
    // size
    printf("File size: %ld bytes\n", file_stat.st_size);
    
    // ownership
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf("Owner: %s (%d)\n", pw ? pw->pw_name : "Unknown", file_stat.st_uid);
    printf("Group: %s (%d)\n", gr ? gr->gr_name : "Unknown", file_stat.st_gid);
    
    // time related info
    printf("Last access time: %s", ctime(&file_stat.st_atime));
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));
    printf("Last status change time: %s", ctime(&file_stat.st_ctime));
    
    // inode info
    printf("Inode number: %ld\n", (long)file_stat.st_ino);
    printf("Number of hard links: %ld\n", (long)file_stat.st_nlink);
    
    return EXIT_SUCCESS;
}

// to print file type
void print_file_type(mode_t mode) {
    if (S_ISREG(mode))
        printf("Regular file\n");
    else if (S_ISDIR(mode))
        printf("Directory\n");
    else if (S_ISLNK(mode))
        printf("Symbolic link\n");
    else if (S_ISFIFO(mode))
        printf("FIFO/pipe\n");
    else if (S_ISSOCK(mode))
        printf("Socket\n");
    else if (S_ISCHR(mode))
        printf("Character device\n");
    else if (S_ISBLK(mode))
        printf("Block device\n");
    else
        printf("Unknown type\n");
}

// print file permissions
void print_file_perm(mode_t mode) {
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}