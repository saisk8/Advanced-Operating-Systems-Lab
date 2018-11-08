#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_BUFFER 1024
#define INPUTFILE "producerInput2.txt"
void main()
{
  //ftok creates a code depending upon actual file and the number you provide.
  key_t key = ftok("/dev/null", 420);

  //create shared memory, if already there give 0666 permission.
  int shmid = shmget(key, MAX_BUFFER, 0666 | IPC_CREAT);

  //attach shared memory.
  char *str = (char*) shmat(shmid, NULL, 0);

  /* Semaphore section */
  sem_t *S1;
  sem_t *S2;
  sem_t *S3;
  S1 = sem_open("S1", 0);
  S2 = sem_open("S2", 0);
  S3 = sem_open("S3", 0);

  sem_wait(S2);
  printf("Write Data : ");

  //getting input from the file.
  FILE *fp;
  if((fp = fopen(INPUTFILE,"r")) == NULL)
    {
      perror("Input file: ");
      exit(1);
    }

  int i;
  char buffer;
  int n;
  fscanf(fp,"%d",&n);

  for(i = 0; i < n; i++)
    {
      fscanf(fp,"%c",&str[i]);
    }

  for(i = 0; i < n; i++)
    {
	    printf("%c ", str[i]);
      //fprintf(fp,"%c ",str[i]);
    }
    sem_post(S3);
}
