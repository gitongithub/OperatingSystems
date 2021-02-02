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
    FILE *fp;
    fp= fopen("para1.txt", "r");
    if(fp == NULL) {
        def_error(-1,"file");
    }
    struct msg mesend;
    key_t key=ftok("osprogram", 455); 
    int msgid = msgget(key, 0666 | IPC_CREAT);
    def_error(msgid,"message_get_error"); 
    mesend.ml = 1; 
    char temp[501];
    while(fgets(temp,501,fp)){
    	    char *p = strtok(temp, " ");
	    while(p!=  NULL){
	    	strcpy(mesend.str,p); 
	    	int me=msgsnd(msgid, &mesend, sizeof(mesend), 0); 
		def_error(me,"message_send_error");
	    	p = strtok(NULL, " ");
	    }
    }
    fclose(fp);
    return 0; 
}
