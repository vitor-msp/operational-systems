#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define ROOT 0

// comandos para o executavel deste arquivo:
// chown root:root
// testar execucao sem ser como root
// chmod u+s
// testar execucao sem ser como root

void showUserInfo()
{
    printf("uid: %d\n", getuid());
    printf("effective uid: %d\n", geteuid());
    printf("gid: %d\n", getgid());
    printf("effective gid: %d\n", getegid());
}

int main(void)
{
    int s, first_time = 0;
    FILE *file;
    mode_t mode = 0700;
    char filepath[15] = "./", filename[] = "only-root.txt", buffer[] = "hello";
    showUserInfo();
    strcat(filepath, filename);
    if (access(filepath, F_OK) != 0)
        first_time = 1;
    if (first_time && getuid() != ROOT)
    {
        printf("must execute at first time as root\n");
        exit(1);
    }
    file = fopen(filepath, "a");
    if (file == NULL)
    {
        printf("user not have permission to access file\n");
        exit(2);
    }
    if (first_time)
        chmod(filepath, mode);
    s = fprintf(file, "%s\n", buffer);
    fclose(file);
    if (s < 0)
        exit(3);
    exit(0);
}