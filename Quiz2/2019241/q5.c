#include <pthread.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
sem_t sem;
pthread_mutex_t mutex;
pthread_t r[6], w;
int nr = 0;
void def_error(int erc,char err[50]){
	if(erc<0){
		perror(err);
        	exit(1); 
	}
}
void *write(void *wn)
{
    int sid = shmget(123454321, 8, IPC_CREAT | 0666);
    def_error(sid,"shared memory");
    int *sm = (int *)shmat(sid,0, 0);
    int se1=sem_wait(&sem);
    def_error(se1,"semaphore");
    *sm=(*sm)+1;
    se1=sem_post(&sem);
    def_error(se1,"semaphore");
}
void *read(void *rn)
{
    int sid = shmget(123454321, 8, IPC_CREAT | 0666);
    def_error(sid,"shared memory");
    int *sm = (int *)shmat(sid, 0, 0);
    pthread_mutex_lock(&mutex);
    if ((++nr) == 1)
        sem_wait(&sem); 
    pthread_mutex_unlock(&mutex);
    printf("R%d read %d\n", *((int *)rn), *sm);
    pthread_mutex_lock(&mutex);
    if ((--nr) == 0)
        sem_post(&sem); 
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int arr[6] = {1, 2, 3, 4, 5, 6};
    int sid = shmget(123454321, 8, IPC_CREAT | 0666);
    def_error(sid,"shared memory");
    int *sm = (int *)shmat(sid,0, 0);
    pthread_mutex_init(&mutex, NULL);
    int se=sem_init(&sem, 0, 1);
    def_error(se,"semaphore");
    *sm = 0;
    int i=0;
    do{
	int i1=0,i2=0;
    	do{
		pthread_create(&r[i1], NULL, (void *)read, (void *)&arr[i1]);
		i1++;
	}while(i1<6);
        pthread_create(&w, NULL, (void *)write, (void *)&arr[0]);
    	do{
        	pthread_join(r[i2], NULL);
		i2++;
    	}while(i2<6);
       	pthread_join(w, NULL);
	i++;
    }while(i<200);
    pthread_mutex_destroy(&mutex);
    int see=sem_destroy(&sem);
    def_error(see,"semaphore");
    see=shmdt(sm);
    def_error(see,"shared memory");
    return 0;
}
