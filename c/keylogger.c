#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>

#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

int main()
{
    char *device = "/dev/input/event4";
    int fd = 0;
    if ((fd = open(device, O_RDONLY)) > 0)
    {
        struct input_event event;
        unsigned int scan_code = 0;
        while (1)
        {
            read(fd, &event, sizeof(struct input_event));
            if (event.value == EV_RELEASED)
            {
                scan_code = event.code;
                printf("%d\n", scan_code);
            }
        }
        close(fd);
    }
    return 0;
}
