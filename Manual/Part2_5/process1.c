#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    FILE *p = fopen("input", "r");
    char temp[1024];
    fscanf(p, "%s", temp);
    char *myfifo = "fifo";
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
    write(fd, temp, sizeof(temp));
    close(fd);
    fclose(p);
    return 0;
}