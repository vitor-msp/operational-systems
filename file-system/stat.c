#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char *argv[])
{
    struct stat file_info;
    mode_t mode = 0760;
    int fd;
    if (strcmp(argv[1], "-f") == 0)
    {
        fd = open(argv[2], O_RDONLY);
    }
    else
    {

        fd = creat("/tmp/test.txt", mode);
    }
    fstat(fd, &file_info);
    close(fd);
    printf("device: %ld\n", file_info.st_dev);
    printf("i-node: %ld\n", file_info.st_ino);
    printf("links: %ld\n", file_info.st_nlink);
    printf("uid: %d\n", file_info.st_uid);
    printf("gid: %d\n", file_info.st_gid);
    printf("dev (if special file) id: %ld\n", file_info.st_rdev);
    printf("size (bytes): %ld\n", file_info.st_size);
    printf("blk size: %ld\n", file_info.st_blksize);
    printf("blocks (512B): %ld\n", file_info.st_blocks);
    printf("access time: %s\n", ctime(&file_info.st_atime));
    printf("modified time: %s\n", ctime(&file_info.st_mtime));
    printf("creation time: %s\n", ctime(&file_info.st_ctime));
}