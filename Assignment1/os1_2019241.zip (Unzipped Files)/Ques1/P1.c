#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <sysexits.h>
#include <errno.h>
#define datasize 400
#define buffsize 6307
struct Student{
	int id;
	char section;
	int m1,m2,m3,m4;
	float avg;
}s_list[datasize];
void calculate_avg(char ch){
	int fd = open("file.csv", O_RDONLY | O_EXCL);
	if(fd==-1){
		perror("file.csv");
		exit(1);
	}
    	char c[buffsize];
	char temp;
    if(read(fd,c,78)==-1)
    	perror("read");
    if(read(fd, c, buffsize)==-1)
    	perror("read");
    int ctr=0;
    char *ptr;
    char *entry[datasize];
    while(ctr<datasize){
    	if(ctr==0)
    		ptr= strtok(c,"\n");
    	else
    		ptr =strtok(NULL,"\n");
    	entry[ctr]=ptr;
    	ctr++;
    }
    ctr=0;
    char *ptr2;
    while(ctr<datasize){
    	ptr2= strtok(entry[ctr],",");
    	s_list[ctr].id=atoi(ptr2);
    	ptr2=strtok(NULL,",");
    	s_list[ctr].section=ptr2[0];
    	ptr2=strtok(NULL,",");
    	s_list[ctr].m1=atoi(ptr2);
    	ptr2=strtok(NULL,",");
    	s_list[ctr].m2=atoi(ptr2);  	
    	ptr2=strtok(NULL,",");
    	s_list[ctr].m3=atoi(ptr2);    	
    	ptr2=strtok(NULL,"\0");
    	s_list[ctr].m4=atoi(ptr2);
    	ctr++;
    }
        close(fd);
	ctr=0;
	for(int i=0;i<datasize;i++){
		if(ch==s_list[i].section){
			s_list[i].avg=(float)(s_list[i].m1+s_list[i].m2+s_list[i].m3+s_list[i].m4)/4;
			char buf[10];
			ssize_t ret=write(1,"Student ID:",strlen("Student ID:"));

			gcvt(s_list[i].id, 3, buf);
			ret=write(1,buf,strlen(buf));
					if(ret==-1)
					perror("write");
			ret=write(1, " ", 1);
					if(ret==-1)
					perror("write");
			ret=write(1,"Student Section:",strlen("Student Section:"));
					if(ret==-1)
					perror("write");
			if(s_list[i].section=='A'){
				ret=write(1,"A Student Average=",strlen("A Student Average="));
						if(ret==-1)
					perror("write");
			}
			else{
				ret=write(1,"B Student Average=",strlen("B Student Average="));
						if(ret==-1)
					perror("write");
			}
			gcvt(s_list[i].avg, 4, buf);
			ret=write(1,buf,strlen(buf));
					if(ret==-1)
					perror("write");
			ret=write(1, " \n", 2);
					if(ret==-1)
					perror("write");
			ctr++;
		}
	}
}
int main(){

    pid_t child=fork();
    int err;
    if(child==0){

    	calculate_avg('A');
    	exit(0);
    }
    else if(child>0){

    	while (waitpid(child, &err, 0) == -1)
            if (errno != EINTR) {
                perror("waitpid");
                exit(EXIT_FAILURE);
         }
             	int fd = open("file.csv", O_RDONLY | O_EXCL);
	if(fd==-1){
		perror("file.csv");
		exit(1);
	}
        
    	calculate_avg('B');
    }
    else{
    	 perror("fork");
         exit(EXIT_FAILURE);
    }


    return 0;
}