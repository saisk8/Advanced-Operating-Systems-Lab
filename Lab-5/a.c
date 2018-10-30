#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int main(int argc, char const *argv[]) {
  struct sysinfo si;
  if (sysinfo(&si) == 0) {
    printf("The number fo process are: %u\n", si.procs);
  } else {
    printf("Some error ocurred\n");
  }
  system("ps -aux");
  return 0;
}
