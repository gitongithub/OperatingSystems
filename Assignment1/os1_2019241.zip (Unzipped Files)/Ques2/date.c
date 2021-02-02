#include <stdio.h> 
#include <time.h>   
#include<string.h>    
#include <sysexits.h>
#include <errno.h>
int main(int argc, char *argv[]) {
    char c[10],temp[10];
    strcpy(temp,argv[1]); 
    time_t rawtime = time(NULL); 
    struct tm *ptm;
    char buf1[4],buf2[4],buf3[6];
    if (rawtime == -1) {
        perror("Error is");
        return 1;
    }    
    if(strcmp(argv[1],"date")==0){
        
        ptm = localtime(&rawtime);
        if (ptm == NULL) {       
            perror("Error is");
            return 1;
        }
        strftime(buf1, 4, "%a", ptm);
        strftime(buf2, 4, "%b", ptm);
        strftime(buf3, 6, "%z", ptm);
        printf("%s %s %02d %02d:%02d:%02d %s %d\n",buf1,buf2,ptm->tm_mday,ptm->tm_hour, ptm->tm_min, ptm->tm_sec,buf3,ptm->tm_year+1900); 
    
    }
   else{
    char *token = strtok(argv[1], " ");
    token = strtok(NULL," ");
    token = strtok(NULL," ");
    if(token!=NULL){
        printf("Command not recognised\n");
        return 1;
    }
    char *token2 = strtok(temp, " ");
    token2 = strtok(NULL," ");
    char p[100];
    strcpy(p,token2);

    if(strcmp("-R",p)==0){
        ptm = localtime(&rawtime);
        if (ptm == NULL) {       
            perror("Error is");
            return 1;
        }
        strftime(buf1, 4, "%a", ptm);
        strftime(buf2, 4, "%b", ptm);
        strftime(buf3, 6, "%z", ptm);
        printf("%s, %02d %s %d %02d:%02d:%02d %s\n",buf1,ptm->tm_mday,buf2,ptm->tm_year+1900,ptm->tm_hour, ptm->tm_min, ptm->tm_sec,buf3);
    }
    else if(strcmp("-u",p)==0){
        ptm = gmtime(&rawtime);
        if (ptm == NULL) {       
            perror("Error is");
            return 1;
        }
        strftime(buf1, 4, "%a", ptm);
        strftime(buf2, 4, "%b", ptm);
        strftime(buf3, 6, "%z", ptm);
        printf("%s %s %02d %02d:%02d:%02d UTC %d\n",buf1,buf2,ptm->tm_mday,ptm->tm_hour, ptm->tm_min, ptm->tm_sec,ptm->tm_year+1900);
    }
    else{
        printf("Command not recognised\n");
    }
}
    return 0;
}