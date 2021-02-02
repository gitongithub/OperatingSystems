#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <stdlib.h>
struct msg { 
    long ml; 
    char str[75]; 
}; 
void def_error(int erc,char err[50]){
	if(erc<0){
		perror(err);
        	exit(1); 
	}
}
int main() 
{ 
    struct msg mesend;
    key_t key=ftok("osprogram",700); 
    int msgid = msgget(key, 0666 | IPC_CREAT); 
    def_error(msgid,"message");
    while(strcmp(mesend.str,"\0")!=0){
         int mr=msgrcv(msgid, &mesend, sizeof(mesend), 1, 0);
         def_error(mr,"message");
	 printf("%s\n",mesend.str); 
    } 
    int mc=msgctl(msgid, IPC_RMID, NULL); 
    def_error(mc,"message");
    return 0; 
}
