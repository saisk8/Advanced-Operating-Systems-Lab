#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct Student {
	int roll;
 	float marks;
};

int main() {
  int pipefd[2];
  pid_t cpid;
  int n, count = 0;
  float average = 0.0;
  char buffer[1024];
  FILE *p = fopen("input", "r");
  FILE *q = fopen("output", "w");
  char string[1024];
  fscanf(p, "%d", &n);
  struct Student student[n];
  for (int i = 0; i < n; i++) {
	fscanf(p, "%d %f", &student[i].roll, &student[i].marks);
	average += student[i].marks;
  }
  average /= n;
  for (int i = 0; i < n; i++) {
  	if (student[i].marks > average) count++;
  }
  sprintf(string, "Number of above average students: %d\n", count);
  pipe(pipefd);
  cpid = fork();
  if (cpid == 0) {
    close(pipefd[1]);
    while (read(pipefd[0], buffer, 1024) > 0)
      ;
    fprintf(q, "%s", buffer);
 	for (int i = 0; i < n; i++) {
	  fprintf(q, "Roll: %d\tMarks: %f\tStatus: ", student[i].roll, student[i].marks);
	  if (student[i].marks > average)
		fprintf(q, "Above average\n");
	 else
		fprintf(q, "Below average\n");
	}
    close(pipefd[0]);
  } else {
    close(pipefd[0]);
    write(pipefd[1], string, strlen(string));
    close(pipefd[1]);
    wait(NULL);
  }
  return 0;
}
