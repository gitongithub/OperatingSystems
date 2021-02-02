#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <ctype.h> 
#include <fcntl.h>
#include <stdlib.h>  
#include <sys/wait.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
sem_t wrt,wrt2;
pthread_mutex_t mutex;
int nr = 0,nr2=0;
int rann(int lower, int upper) 
{ 
        int i; 
        int num = (rand() % (upper - lower + 1)) + lower; 
        return num; 
} 
void writerint()
{
    int key2=12;
    int shmid2 = shmget(key2, 8, IPC_CREAT | 0666);
    int *c = (int *)shmat(shmid2, (void *)0, 0);
    sem_wait(&wrt2);
    *c =(*c+1);
    sem_post(&wrt2);
}
void readerint()
{
    int key2=12;
    int shmid2 = shmget(key2, 8, IPC_CREAT | 0666);
    int *c = (int *)shmat(shmid2, (void *)0, 0);
    nr2++;
    if (nr2 == 1)
    {
        sem_wait(&wrt2);
    }
    printf("Reader Read  %d\n", *c);
    nr2--;
    if (nr2 == 0)
    {
        sem_post(&wrt2); 
    }

}
void writer()
{
    int key=11;
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    int k=rann(0,4);
    if(k==0)
	strcpy(cnt,"abcd");
    else if(k==1){
        strcpy(cnt,"khilop");
    }
    else if(k==2){
        strcpy(cnt,"dino");
    }
    else{
        strcpy(cnt,"qwerty");
    }
        
    sem_post(&wrt);
}
void reader()
{
    int key=11;
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    nr++;
    if (nr == 1)
    {
        sem_wait(&wrt);
    }
    printf("Reader read count as %s\n", cnt);
    nr--;
    if (nr == 0)
    {
        sem_post(&wrt); 
    }

}

int main()
{
    int key=11;
    int shmid = shmget(key, 8, IPC_CREAT | 0666);
    if (shmid<0)
    {
        perror("shared memory");
	exit(1);
    }
    char *cnt = (char *)shmat(shmid, (void *)0, 0);
    strcpy(cnt,"whatareyoudoing");
    int key2=12;
    int shmid2 = shmget(key2, 8, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("af");
    }
    int *c = (int *)shmat(shmid2, (void *)0, 0);
    *c=0;
    sem_init(&wrt, 0, 1);
    sem_init(&wrt2, 0, 1);
    int pid=fork();
    if(pid>0){
        wait(NULL);
	char temp[500];
        printf("%s",temp); 
        for(int i=0;i<5;i++){
		writer();
		reader();
		writerint();
		readerint();
        }
    }
    else{
    for(int i=0;i<5;i++){
		writer();
		writerint();
		readerint();
		reader();
    }
	exit(0);
    }
    int shmi=sem_destroy(&wrt);
    if (shmi<0)
    {
        perror("shared memory");
	exit(1);
    }
    shmi=sem_destroy(&wrt2);
    if (shmi<0)
    {
        perror("shared memory");
	exit(1);
    }
    shmi=shmdt(cnt);
    if (shmi<0)
    {
        perror("shared memory");
	exit(1);
    }
    shmi=shmdt(c);
    if (shmi<0)
    {
        perror("shared memory");
	exit(1);
    }
    return 0;
}
