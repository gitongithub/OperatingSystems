#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>

int x = 10;

int main()
{
    pid_t pid=fork();
    if (pid == 0)
    {
        while (x > -90)
        {
            x--;
        printf("child process%d\n", x);
        }
        int s;
        s=printf("Value thorugh child process: %d\n", x);
        if(s==-1){
            perror("Print error");
            exit(1);
        }
        exit(0);
    }
    else if (pid > 0)
    {
        while (x < 100)
        {
            x++;
        printf("parent process%d\n", x);
        }
        int s;
        s=printf("Value through parent process: %d\n", x);
        if(s==-1){
            perror("Print error");
            exit(1);
        }
    }
    else
    {
        perror("Error in fork");
        return 1;
    }
    return 0;
}
