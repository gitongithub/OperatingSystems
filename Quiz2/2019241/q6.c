#include <stdio.h> 
#include <pthread.h> 
#include<unistd.h>
#include <semaphore.h> 
#include<stdlib.h>
sem_t semaphore[5],mutex; 
void eat_start(int);
void eat_done(int) ;
void print_result(int);
int st[5]; 
void* cthread(void*);
// to avoid deadlock, we used condition that philosopher only picks forks when both of them are available
int main() 
{ 
    int plist[5] = {0,1,2,3,4}; 
    pthread_t ptid[5]; 
    if(sem_init(&mutex, 0, 1)<0)
    {
	perror("semaphore"); 
	exit(1);
    }
    int i1=0,i2=0,i3=0;
    do{
        if(sem_init(&semaphore[i1], 0, 0)<0)
    	{
		perror("semaphore"); 
		exit(1);
    	}
	i1++;
    }while(i1<5); 
    do{ 
        if(pthread_create(&ptid[i2], NULL, cthread, &plist[i2])!=0)
    	{
		perror("Thread"); 
		exit(1);
    	}
	i2++;
    }while(i2<5);
    do{ 
        if(pthread_join(ptid[i3], NULL))
    	{
		perror("Thread"); 
		exit(1);
    	}
	i3++;
    }while(i3<5);
    return 0;
} 
void* cthread(void* num) 
{ 
    int ii=0;
    do{ 
        int* i = num; 
        eat_start(*i);  
        eat_done(*i);
	ii++; 
    }while(ii<1);
    pthread_exit(NULL);
}  
void eat_start(int pn) 
{ 
    if(sem_wait(&mutex)<0) 
    {
	perror("semaphore"); 
	exit(1);
    }
    st[pn] = 2; 
    if (st[pn] == 2) { 
	if(st[(pn + 4) % 5] != 3 && st[(pn + 1) % 5] != 3)
		print_result(pn);
    } 
    if(sem_post(&mutex)<0)
    {
	perror("semaphore"); 
	exit(1);
    } 
    if(sem_wait(&semaphore[pn])<0)
    {
	perror("semaphore"); 
	exit(1);
    }
    sleep(0); 
} 
void print_result(int pn){
	sleep(1);
        st[pn] = 3; 
        printf("P%d recieves F%d,F%d\n", pn+1, (pn + 1) % 5 +1, pn+1); 
        sem_post(&semaphore[pn]); 
}
void eat_done(int pn) 
{ 
    if(sem_wait(&mutex)<0)
    {
	perror("semaphore"); 
	exit(1);
    }
    st[pn] = 1;
    int t1=(pn + 1) % 5;
    int t2=(pn + 4) % 5;
    if (st[t1] == 2) { 
	if(st[(t1 + 4) % 5] != 3 && st[(t1 + 1) % 5] != 3)
		print_result(t1);
    } 
    if (st[t2] == 2) { 
	if(st[(t2 + 4) % 5] != 3 && st[(t2 + 1) % 5] != 3)
		print_result(t2);
    } 
    if(sem_post(&mutex)<0) 
    {
	perror("semaphore"); 
	exit(1);
    }
} 

