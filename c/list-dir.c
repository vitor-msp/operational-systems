#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
// #include <time.h>
// #include <string.h>

void main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entrydir;
    char cwd[128];
    getcwd(cwd, sizeof(cwd));
    dir = opendir(cwd);
    while (1)
    {
        entrydir = readdir(dir);
        if (entrydir == NULL)
            break;
        printf("=====================\n");
        printf("file name: %s\n", entrydir->d_name);
        printf("type: %c\n", entrydir->d_type);
        printf("i-node: %ld\n", entrydir->d_ino);
    }
    closedir(dir);
}