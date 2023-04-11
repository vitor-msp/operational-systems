#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

void main(int argc, char *argv[])
{
    mode_t mode = 0700;
    int old_fd = open(argv[1], O_RDONLY);
    int new_fd = creat(argv[2], mode);
    char buffer[BUFFER_SIZE];
    int rd_count;
    off_t offset = 4;
    lseek(old_fd, offset, SEEK_CUR);
    while (1)
    {
        rd_count = read(old_fd, buffer, BUFFER_SIZE);
        if (rd_count <= 0)
            break;
        write(new_fd, buffer, rd_count);
    }
    close(old_fd);
    close(new_fd);
}