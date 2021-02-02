#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <unistd.h>
#include<stdlib.h>
int main (int argc, char *argv[]) 
{ 
    char *token = strtok(argv[1], " ");
    char **arr = (char **)malloc(10 * sizeof(char *));
    int j = 0;
    token = strtok(NULL, " ");
    while (token != NULL)
    {
        arr[j] = (char *)malloc(1022 * sizeof(char));
        strcpy(arr[j], token);
        if((arr[j][0]=='-'&&j>0)||((arr[j][0]=='-' && j==0)&& (arr[j][1]!='d' && arr[j][1]!='v'))){
            printf("Invalid operand -- %c\n",arr[j][1]);
            return 1;
        }
        token = strtok(NULL, " ");
        j++;
    }
    if(j==0){
        printf("missing operand");
        return 1;
    }
    else if(strcmp(arr[0],"-d")==0){
    	j=1;
    	while(arr[j]!=NULL){
    		if (rmdir(arr[j]) != 0){
    			perror(arr[j]);
   		    }
   		    j++;
        }
        if(j==1)
        	printf("no operand provided \n");

    }
    else if(strcmp(arr[0],"-v")==0){
    	j=1;
    	while(arr[j]!=NULL){
    		if (unlink(arr[j]) == 0){
    			printf("removed '%s'\n",arr[j]);
   		    }
   		    else
   		    	perror(arr[j]);
   		    j++;
        }
        if(j==1)
        	printf("no operand provided \n");
    }
    else if(arr[0][0]=='-'){
    	printf("Invalid operand - \n");
    }
    else{
    	j=0;
    	while(arr[j]!=NULL){
    		if (unlink(arr[j]) != 0){
    			perror(arr[j]);
   		    }
   		    j++;
        }
        if(j==0)
        	printf("no operand provided \n"); 	
    }
    return 0; 
} 
