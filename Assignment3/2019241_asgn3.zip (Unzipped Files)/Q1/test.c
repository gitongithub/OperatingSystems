/* Name: Gitansh Raj Satija
Roll_Number: 2019241 */
#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
int main() {
	long rtinp;
	struct timeval time1,time2;
	printf("Enter valid rtnice value:");
	scanf("%ld",&rtinp);
	long pid = fork();
        gettimeofday(&time1, NULL);
	if(pid < 0) {
		perror("fork error");
		exit(errno);
	}
	else if(pid != 0) {
		long i=0;
		do{
			
			i++;
		}while(i<1000000000);
		gettimeofday(&time2, NULL);		
		double parT= (double) (time2.tv_usec-time1.tv_usec)/1000 + (double) (time2.tv_sec-time1.tv_sec)*1000;
		printf("Execution time taken by parent = %lf\n",parT);
		//wait(NULL);
	}
	else {
		long pid_update=getpid();
		int sc=syscall(336,pid_update,rtinp);
		if(sc != 0) {
			printf("Error in syscall. Check kernel logs\n");
		}
		long i=0;
		do{
			i++;
		}while(i<1000000000);
		gettimeofday(&time2, NULL);
		double childT= (double) (time2.tv_usec-time1.tv_usec)/1000 + (double) (time2.tv_sec-time1.tv_sec)*1000;
		printf("Execution time taken by child = %lf\n",childT);
	}
	return 0;
}
