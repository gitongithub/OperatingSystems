#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
//gitansh 2019241
int nop;
void def_error(int erc,char err[50]){
    if(erc!=0){
        perror(err);
            exit(1); 
    }
}
struct my_semaphore
{
    pthread_mutex_t lck;
    int sig_value;
}b,try_eat,*fork_sem;
int my_semaphore_init(struct my_semaphore *my_sem, int c)
{
    int erc;
    if (my_sem==NULL)
        return -1;
    my_sem->sig_value = c;
    erc = pthread_mutex_init(&(my_sem->lck), NULL);
    def_error(erc,"Semaphore creation error");
    return 0;
}
int printSignalValue(struct my_semaphore *my_sem)
{
    if(my_sem==NULL)
    return -1;
    return my_sem->sig_value;   
    
}
int signal(struct my_semaphore *my_sem)
{
    int erc;
    if (my_sem==NULL)
        return -1;
    erc = pthread_mutex_lock(&(my_sem->lck));
    def_error(erc,"lock");
    my_sem->sig_value=my_sem->sig_value+1;
    erc = pthread_mutex_unlock(&(my_sem->lck));
    def_error(erc,"unlock");
    return 0;
}
int wait(struct my_semaphore *my_sem)
{
    int erc;
    if (my_sem==NULL)
        return -1;
    erc = pthread_mutex_trylock(&(my_sem->lck));
    if(!(erc==0))
    return 1;
    while (my_sem->sig_value == 0)
    {
        erc = pthread_mutex_unlock(&(my_sem->lck));
        def_error(erc,"unlock");
        return 1;
    }
    my_sem->sig_value=my_sem->sig_value-1;
    erc = pthread_mutex_unlock(&(my_sem->lck));
    def_error(erc,"unlock");
    return 0;
}

void checkSignal(struct my_semaphore *my_sem,int max){
        int val =printSignalValue(my_sem);
        if (val < 0 || max< val){
            printf("Error in Semaphore signal  %d\n", val);
        exit(1);
    }

}
void *cthread(void *arg)
{
    int t,*id =arg,erc;
    do{
    sleep(1);
        t = wait(&try_eat);
    if(t==1){
            do
            {
                    t = wait(&try_eat);
            }while(t==1);    
    }
        checkSignal(&try_eat, nop-1);
        t = wait(&fork_sem[(*id+nop-1)%nop]);
    if(t==1){
            do
            {
                t = wait(&fork_sem[(*id+nop-1)%nop]);
            }while(t==1);    
    }
        checkSignal(&fork_sem[(*id+nop-1)%nop],1);
        t = wait(&fork_sem[*id]);
    if(t==1){
            do
            {
                t = wait(&fork_sem[*id]);
            }while(t==1);    
    }
        checkSignal(&fork_sem[*id], 1);
        t = wait(&b);
    if(t==1){
            do
            {
                t =wait(&b);
            }while(t==1);    
    }
        checkSignal(&b, 1);
        printf("Philosopher %d eats using forks %d and %d\n", *id +1, (*id+nop-1)%nop +1, *id +1);
        sleep(1);
        signal(&b);
        checkSignal(&b, 1);
        signal(&fork_sem[(*id + nop-1) % nop]);
        checkSignal(&fork_sem[(*id + nop-1) % nop],1);
        //printf("Philosopher %d has put down fork %d\n", *id+1, (*id + nop-1) % nop+1);
        signal(&fork_sem[*id]);
        checkSignal(&fork_sem[*id], 1);
        //printf("Philosopher %d has put down fork %d\n", *id+1, *id+1);
        signal(&try_eat);
        checkSignal(&try_eat, nop-1);
    }while(1);
    pthread_exit(NULL);
}

void initialize_sem(){
    int i=0;
        if(my_semaphore_init(&b, 1)==-1){
        printf("Error in creating semaphore");
        exit(1);
        }
        if(my_semaphore_init(&try_eat, nop - 1)==-1){
        printf("Error in creating semaphore");
        exit(1);    
    }
    do{
            if(my_semaphore_init(&fork_sem[i], 1)==-1){
            printf("Error in creating semaphore");
            exit(1);
        }
            i++;
        }while(i<nop);
}

int main()
{
    int i=0,j=0,psize=sizeof(int *),erc;
    fork_sem = malloc(nop * sizeof(struct my_semaphore));
    char s[]="Enter Number of Philosophers:";
    if(write(1,s,strlen(s))==-1){
    perror("write");
    exit(1);
    }
    scanf("%d", &nop);
    if(nop<1)
    {
	printf("Too few philosophers\n");
	exit(0);
    }
    pthread_t philosophers[nop];
    initialize_sem();
    do{
        int *arg = malloc(psize);
    *arg=i;
        int res = pthread_create(&philosophers[i], NULL, cthread, (void *)arg);
        def_error(res,"Thread create");
    i++;
    }while(i<nop);
    do{
        erc=pthread_join(philosophers[j], NULL);
    def_error(erc,"thread join");
    j++;
    }while(j<nop);
    return 0;
}
