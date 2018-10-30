#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_BUF 1024

int main(void) {
  int fd;
  FILE *p = fopen("output", "w");
  char *myfifo = "fifo";
  char buf[MAX_BUF];
  fd = open(myfifo, O_RDONLY);
  read(fd, buf, MAX_BUF);
  fprintf(p, "%s\n", buf);
  close(fd);
  fclose(p);
  return 0;
}