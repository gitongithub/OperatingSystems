#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 10;

void *cthread(void *arg)
{
    while (x > -90)
    {
        x--;
        printf("child thread:%d\n", x);
    }
    int s;
    s=printf("Value through Child thread: %d\n", x);
        if(s==-1){
            perror("Print error");
            exit(1);
        }
}
void pthread(){
    while (x < 100)
    {
        x++;
        printf("parent thread:%d\n", x);
    }
    int s;
    s=printf("Values from parent thread: %d\n", x);
        if(s==-1){
            perror("Print error");
            exit(1);
        }
}
int main(void)
{
    pthread_t thd;
    if(pthread_create(&thd, NULL, &cthread, NULL)){
         perror("Thread create error");
         exit(1);
    }
    pthread();

    if(pthread_join(thd, NULL)){
        perror("Thread join error");
        exit(1);
    }
    return 0;
}
