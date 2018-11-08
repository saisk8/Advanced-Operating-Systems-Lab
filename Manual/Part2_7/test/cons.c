#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_BUFFER 1024
#define OUTPUTFILE "outputfile.txt"
#define INPUTFILE "producerInput.txt"

void main()
{

	key_t key = ftok("/dev/null", 420);

	int shmid = shmget(key,	MAX_BUFFER, 0666|IPC_CREAT);

	char *str = (char *) shmat(shmid, NULL, 0);


	/*semaphore section*/
	sem_t *S1;
	S1 = sem_open("S1", 0);
	sem_t *S2;
	S2 = sem_open("S2", 0);
	sem_t *S3;
	S3 = sem_open("S3", 0);

	int n = 2; // two producer to read from
	while(n--)
	{
	sem_wait(S1);
	sem_wait(S3);
	printf("\nData read from the memory: ");

	int i=0;

	while(str[i])
	{
		printf("%c ", str[i]);
		i++;
	}
	sem_post(S2);
	sem_post(S1);
	/*if(!n)
	{
		sem_unlink("S1");
		sem_unlink("S2");
		sem_unlink("S3");
	}*/
}

/*
	FILE *fp;
	if((fp = fopen(OUTPUTFILE,"w")) == NULL)
	{
		perror("Input file: ");
		exit(1);
	}
//	i = 0;
	while(str[i])
	{
		fprintf(fp,"%c ",str[i]);
		i++;
	}
*/

}
