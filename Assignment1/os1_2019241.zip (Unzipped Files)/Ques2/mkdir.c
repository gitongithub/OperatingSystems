#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include<string.h>   
int main(int argc, char *argv[]) 
{ 
    char *token = strtok(argv[1], " ");
    char **arr = (char **)malloc(10 * sizeof(char *));
    int j = 0;
    token = strtok(NULL, " ");
    while (token != NULL)
    {
        arr[j] = (char *)malloc(1022 * sizeof(char));
        strcpy(arr[j], token);
        if((arr[j][0]=='-'&&j>0)||((arr[j][0]=='-' && j==0)&& (arr[j][1]!='v' && arr[j][1]!='m'))){
            printf("Invalid operand -- %c\n",arr[j][1]);
            return 1;
        }
        token = strtok(NULL, " ");
        j++;
    }
    int check; 
    if(j==0){
        printf("missing operand");
        return 1;
    }
    j=0;
    if(strcmp(arr[0],"-v")==0){
                j=1;
                
        while(arr[j]!=NULL){
            char* dirname = arr[j]; 
            check = mkdir(dirname,0777);  
            if (!check) 
                printf("mkdir:Directory created '%s'\n",arr[j]); 
            else { 
                perror(arr[j]);
            }  
            j++;
        }
        if(j==1)
            printf("missing operand\n");
        
    }
    else if(arr[0][0]=='-'&&arr[0][1]=='m'&&arr[0][2]=='='){
        j=1;
        char mode[5]="";
        for(int i=3;i<7&&arr[0][i]!='\0';i++){
            mode[i-3]=arr[0][i];
        }
        int k=0777;
        if(atoi(mode)==400)
            k=0400;
        else if(atoi(mode)==0777)
            k=0777;
        else if(atoi(mode)==100)
            k=0100;
        else if(atoi(mode)==0200)
            k=0200;
        else{
            printf("unrecognuzed mode\n");
            return 1;
        }
        while(arr[j]!=NULL){
            char* dirname = arr[j];
             
            check = mkdir(dirname,k);  
            if (check) 
                perror(arr[j]);
            j++;
        }
        if(j==1)
            printf("missing operand\n");
    }
    else{

        while(arr[j]!=NULL){
            char* dirname = arr[j]; 
            check = mkdir(dirname,0777);  
            if (check) 
                perror(arr[j]);
            j++;
        }
        if(j==0)
            printf("missing operand\n");
    }
  return 0;
}