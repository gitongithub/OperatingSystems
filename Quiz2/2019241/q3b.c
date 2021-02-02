#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
void def_error(int erc,char err[50]){
	if(erc<0){
		perror(err);
        	exit(1); 
	}
}
int main()
{
    struct sockaddr_in sr;
    memset(&sr, 0, sizeof(sr));
    char buff[501];
    FILE *fp;
    fp = fopen("para2.txt", "r");
    if(fp == NULL)
        def_error(-1,"file");
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    def_error(sfd,"socket"); 
    sr.sin_family = AF_INET;
    sr.sin_port = htons(5001);
    sr.sin_addr.s_addr = INADDR_ANY;
    while(fgets(buff, 501, fp))
    {
	    char *p = strtok(buff, " ");
	    char temp[501];
	    while(p!=NULL)
	    {
		strcpy(temp, p);
		int st=sendto(sfd, temp, strlen(temp), MSG_CONFIRM, (const struct sockaddr *)&sr, sizeof(sr));
		def_error(st,"message_send_error");     
		p = strtok(NULL, " ");
	    }
    }
    fclose(fp);
    int cl=close(sfd);
    def_error(cl,"close_error");
    return 0;

}
