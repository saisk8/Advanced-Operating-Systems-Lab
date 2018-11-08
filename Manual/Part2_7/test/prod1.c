#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_BUFFER 1024
#define INPUTFILE "producerInput.txt"
void main()
{
  /*
  ### Shared memory section ###
  */

  //ftok creates a code depending upon actual file and the number you provide.
  key_t key = ftok("/dev/null", 420);

  key_t semkey = 1234;
  int semflag = IPC_CREAT | 0666;;
  int nsems = 1;
  int nsops; // number of operations to do
  int semid = semget(semkey, nsems, semflag);
  //create shared memory, if already there give 0666 permission.
  int shmid = shmget(key, MAX_BUFFER, 0666 | IPC_CREAT);

  //attach shared memory.
  char *str = (char*) shmat(shmid, NULL, 0);

  /*
  ### Semaphore section ###
  */

  sem_t *S1; // initialize semaphore
  S1 = sem_open("S1", O_CREAT, 0777, 0);
  sem_t *S2; // initialize semaphore
  S2 = sem_open("S2", O_CREAT, 0777, 0);
  sem_t *S3; // initialize semaphore
  S3 = sem_open("S3", O_CREAT, 0777, 0);

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
  //int n = (int)buffer;
  printf("\n Value of n: %d. \n", n);
  for(i = 0; i < n; i++)
    {
      fscanf(fp,"%c",&str[i]);
    }

  for(i = 0; i < n; i++)
    {
	    printf("%c ", str[i]);
      //fprintf(fp,"%c ",str[i]);
    }
  sem_post(S1);
  sem_post(S3);
}
