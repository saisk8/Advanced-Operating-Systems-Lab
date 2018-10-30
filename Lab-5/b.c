#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
  struct sysinfo memDetails;
  if (sysinfo(&memDetails) == 0) {
    long long totalVirtualMem = memDetails.totalram;
    totalVirtualMem += memDetails.totalswap;
    totalVirtualMem *= memDetails.mem_unit;
    printf("Total memory: %llu\n", totalVirtualMem);
    long long virtualMemUsed = memDetails.totalram - memDetails.freeram;
    virtualMemUsed += memDetails.totalswap - memDetails.freeswap;
    virtualMemUsed *= memDetails.mem_unit;
    long double avarageMemUsed = virtualMemUsed / memDetails.procs;
    printf("The average memory used: %Lf\n", avarageMemUsed);
  }
  return 0;
}
