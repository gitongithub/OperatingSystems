#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 
void def_error(int erc,char err[50]){
	if(erc<0){
		perror(err);
        	exit(1); 
	}
}
int main() { 
    char str[1002];
    struct sockaddr_in sadr, cadr;  
    memset(&sadr, 0, sizeof(sadr)); 
    memset(&cadr, 0, sizeof(cadr)); 
    int port=5001,sfd=socket(AF_INET, SOCK_DGRAM, 0),len=sizeof(cadr),n; 
    def_error(sfd,"socket"); 
    sadr.sin_family = AF_INET;
    sadr.sin_addr.s_addr = INADDR_ANY; 
    sadr.sin_port = htons(port); 
    int bd=bind(sfd, (const struct sockaddr *)&sadr,sizeof(sadr));
    def_error(bd,"bind");
    n = recvfrom(sfd, str, 1002,MSG_WAITALL, ( struct sockaddr *) &cadr, &len); 
    def_error(n,"message_receive_failure");
    str[n] = '\0'; 
    printf("%s\n",str); 
    while(str!=NULL){
         n = recvfrom(sfd, str, 1002,MSG_WAITALL, ( struct sockaddr *) &cadr, &len); 
         def_error(n,"message_receive_failure");
         str[n] = '\0'; 
         printf("%s\n", str); 
}
    close(sfd);
    return 0; 
}
