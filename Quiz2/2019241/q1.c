#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdlib.h>  
#include <sys/wait.h> 
#include <sys/types.h> 
#include <unistd.h>  
int pipe1[2],pipe2[2];
int main() 
{ 
  int pid,pst1 = pipe(pipe1),pst2=pipe(pipe2); 
  if(pst1 < 0 || pst2<0 ){
    perror("pipe");
    exit(1);
  }
  if((pid=fork())<0){
    perror("fork");
    exit(1);
  } 
  else if(pid> 0){
    int k1=close(pipe1[0]);
    int k2=close(pipe2[1]);
    if(k1<0 || k2<0 ){
    	perror("close");
    	exit(1);
    }
    char str[500];
    fgets(str, 500, stdin);
    write(pipe1[1] , str ,500);
    int k=wait(NULL);
    if(k<0 ){
    	perror("wait");
    	exit(1);
    }
    read(pipe2[0] , str ,500);
    printf("%s", str);
  }
  else{
	int i=0;
    	close(pipe2[0]); 
    	close(pipe1[1]); 
	char temp[500];
    	read(pipe1[0] , temp , 500);  
    	while(temp[i]!='\0'){
		if(temp[i] == (char)'\\'){
			int f=0;
   			switch(temp[i+1]) {
      				case 'a' : f=2;
        				  break;
      				case 'b' :f=2;
					  break;
      				case 'f' :f=2;
         				  break;
      				case 'n' :f=1;
         				  break;
      				case 'r' :f=2;
         				  break;
      				case 't' :f=2;
         				  break;
      				case 'v' :f=2;
         				  break;
      				default  : f=0;
   			}
        		if(f==1){
       			 	temp[i] = '\0';
        		 	break;
        		}
			else if(f==0){
				temp[i+1]-=32;
			}
			i++;
			i++;
      		}
      		else if(temp[i]>='a' && temp[i]<='z')
      		{
        		temp[i]-=32;
			i++;
      		}
		else{
			i++;
		}	
   	}
    	write(pipe2[1],temp,500);
    	exit(0);
  }
  return 0;
}
