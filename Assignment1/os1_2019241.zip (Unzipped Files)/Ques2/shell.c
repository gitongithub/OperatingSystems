#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sysexits.h>
static char hist_list[1000][1024];
char commands[10][10] = {"echo", "cd", "date", "pwd", "ls", "cat", "mkdir", "rm", "history", "exit"};
static int counter = 0;
int exit_status = 0;
int main()
{
    char cwd[1024];
    while (exit_status == 0)
    {
        int inp_size = 0, fno = -1;
        char inp_cmd[1024];
        char arr[1024];
        printf("%s>$",getcwd(arr, sizeof(arr)));
        scanf("%[^\n]%*c", inp_cmd);
        if(inp_cmd[0]==0){
            printf("exitting [PROCESS TERMINATED....]\n");
            exit(0);
        }
        char tt[1024];
        strcpy(tt, inp_cmd);
        strcpy(hist_list[counter], inp_cmd);
        counter++;
        char *ptr = strtok(inp_cmd, " ");
        char **inparr = (char **)malloc(1024 * sizeof(char *));
        int i=0;
        while (ptr != NULL)
        {
            inparr[inp_size] = (char *)malloc(1024 * sizeof(char));
            strcpy(inparr[inp_size], ptr);
            ptr = strtok(NULL, " ");
            inp_size++;
        }
        do
        {
            int f = 0;
            int counter = 0;
            while (commands[i][counter] != '\0' && inparr[0][counter] != '\0')
            {
                if (commands[i][counter] != inparr[0][counter])
                {
                    f = 1;
                    break;
                }
                counter++;
            }
            if (commands[i][counter] != '\0')
                f = 1;
            if( inparr[0][counter] != '\0')
                f=1;
            if (f == 0)
            {
                fno = i + 1;
                break;
            }
            i++;
        } while (i <= 9);

        if (fno == 1)
        {
            if (inparr[1] == NULL)
            {
                printf("\n");
            }
            else
            {
                if (strcmp(inparr[1], "-E") == 0)
                {
                    int f1=0;
                    for (int i = 2; i < inp_size; ++i)
                    {
                        if (inparr[i] != NULL)
                        {
                            for(int j=0;inparr[i][j]!='\0';j++){
                                    if(inparr[i][j]==47 &&f1==0){
                                        f1=1;
                                        continue;
                                    }
                                    else{
                                        printf("%c",inparr[i][j]);
                                    }

                            }
                            printf(" ");
                            
                        }
                    }
                    printf("\n");

                }
                else if (strcmp(inparr[1], "--help") == 0)
                {
                    printf("echo - display a line of text");
                }
                else if (strcmp(inparr[1], "-n") == 0)
                {
                    for (int i = 2; i < inp_size; ++i)
                    {
                        if (inparr[i] != NULL)
                        {
                            printf("%s", inparr[i]);
                        }
                        if (i != inp_size - 1)
                            printf(" ");
                    }
                }
                else
                {
                    for (int i = 1; i < inp_size; ++i)
                    {
                        if (inparr[i] != NULL)
                        {
                            printf("%s ", inparr[i]);
                        }
                    }
                    printf("\n");
                }
            }
        }
        else if (fno == 2){

            char ci[1024];
            int f=0;
            if (inparr[1] == NULL)
            {
                f=1;
            }
            else
            {
                strcpy(ci, inparr[1]);
 
            }

            if (f==1)
            { 

                char cwd[1024];
                if (chdir(getenv("HOME")) == 0)
                {

                    char *cwd_it = getcwd(cwd, sizeof(cwd));
                    printf("%s\n", cwd_it); 
                }
                else
                {
                    perror("");
                }
            }
            else if (strcmp(ci, "~")==0)
            { 

                char cwd[1024];
                if (chdir(getenv("HOME")) == 0)
                {

                    char *cwd_it = getcwd(cwd, sizeof(cwd));
                    printf("%s\n", cwd_it); 
                }
                else
                {
                    perror("");
                }
            }
            else if (strcmp(ci, "--")==0)
            { 

                char cwd[1024];
                if (chdir(getenv("HOME")) == 0)
                {

                    char *cwd_it = getcwd(cwd, sizeof(cwd));
                    printf("%s\n", cwd_it); 
                }
                else
                {
                    perror("");
                }
            }
            else if (strcmp(ci, "-P") == 0)
            {
                char cwd_inputnew2[1024];
                if (inparr[2] != NULL)
                {
                    strcpy(cwd_inputnew2, inparr[2]);
                    char *pt = strtok(cwd_inputnew2, "\n");
                    char buf[PATH_MAX];
                    char *res = realpath(pt, buf);
                    if (res)
                    {

                        //printf("%s\n%s\n", buf,res);
                        char temp[1024];
                        if (chdir(res) == 0) 
                        {

                            char *cw = getcwd(temp, sizeof(temp));
                        }
                        else
                        {
                            perror("");
                        }
                    }
                    else
                    {
                        perror("");
                    }
                    
                }

                else
                {
                    char cwd[1024];
                    if (chdir(getenv("HOME"))== 0)
                    {

                        char *temp = getcwd(cwd, sizeof(cwd));
                        //printf("%s\n", temp);
                    }
                    else
                    {
                        perror("");
                    }
                }
            }

            else if (strcmp(ci, "-L") == 0)
            {
                if (inparr[2] != NULL)
                {
                    char cwd_inputnew2[1024];
                    strcpy(cwd_inputnew2, inparr[2]);
                    char *pt = strtok(cwd_inputnew2, "\n");
                    char cwd[1024];
                    if (chdir(pt) == 0)
                    {
                        char *temp = getcwd(cwd, sizeof(cwd));
                        //printf("%s\n", temp);
                    }
                    else
                    {
                        perror("");
                    }
                    
                }
                else
                {
                    char cwd[1024];
                    if ( chdir(getenv("HOME"))== 0)
                    {

                        char *cwd3 = getcwd(cwd, sizeof(cwd));
                        //printf("%s\n", cwd3);
                    }
                    else
                    {
                        perror("");
                    }
                }
            }
            else
            {
                char *pt = strtok(ci, "\n");
                 char cwd[1024];
                if (chdir(pt)== 0)
                {
                    char *cwd1 = getcwd(cwd, sizeof(cwd));
                }
                else
                {
                    perror("");
                }
            }
        }
        else if (fno == 3)
        {

            pid_t id=fork();
            if (id == 0)
            {
                char *args[] = {"./date", tt, NULL};
                execvp("./date", args);
                exit(0);
            }
            else if (id>0){
                int st;
                pid_t cpid;
                cpid = wait(&st);
                if(cpid<0)
                    perror("wait");
            }
            else
            {
                perror("fork");
            }
        }
        else if (fno == 4)
        {
            char cwd_input[100];
            char arr[1024];
            char *cwd = getcwd(arr, sizeof(arr));

            if (inparr[1] != NULL)
                strcpy(cwd_input, inparr[1]);
            if (cwd != NULL)
            {
                            if(inparr[1]!=NULL && inparr[1][1]=='L'){
                     char newarr[1024];
                    char *cwd2 = getenv(cwd);
                    cwd2 = getcwd(newarr, sizeof(newarr));
                    printf("%s\n", cwd2);
              
            }

                else if (strcmp(cwd_input, "--help") == 0)
                {
                    printf("pwd - print name of current/working directory");
                    exit;
                }
                else if (strcmp(cwd_input, "-P") == 0)
                {
                    char newarr[1024];
                    char *cwd2 = getcwd(newarr, sizeof(newarr));
                    printf("%s\n", cwd2);
                }
                else if (inparr[1] != NULL && inparr[1][0] == '-' && inparr[1][1]!='L')
                {
                    printf("unrecognized Command\n");
                }
                else
                {
                    printf("%s\n", cwd);
                }
            }
            else 
            {
                perror("pwd");
            }
        }
        else if (fno == 5)
        {
            pid_t id=fork();
            if (id == 0)
            {
                char *args[] = {"./ls", tt, NULL};
                execvp("./ls", args);
                exit(0);
            }
            else if (id>0){
                int st;
                pid_t cpid;
                cpid = wait(&st);
                if(cpid<0)
                    perror("wait");
            }
            else
            {
                perror("fork");
            }

        }
        else if (fno == 6)
        {
            pid_t id=fork();
            if (id == 0)
            {
                char *args[] = {"./cat", tt, NULL};
                execvp("./cat", args);
                exit(0);
            }
            else if (id>0){
                int st;
                pid_t cpid;
                cpid = wait(&st);
                if(cpid<0)
                    perror("wait");
            }
            else
            {
                perror("fork");
            }
        }
        else if (fno == 7)
        {
            pid_t id=fork();
            if (id == 0)
            {
                char *args[] = {"./mkdir", tt, NULL};
                execvp("./mkdir", args);
                exit(0);
            }
            else if (id>0){
                int st;
                pid_t cpid;
                cpid = wait(&st);
                if(cpid<0)
                    perror("wait");
            }
            else
            {
                perror("fork");
            }
        }
        else if (fno == 8)
        {
            pid_t id=fork();
            if (id == 0)
            {
                char *args[] = {"./rm", tt, NULL};
                execvp("./rm", args);
                exit(0);
            }
            else if (id>0){
                int st;
                pid_t cpid;
                cpid = wait(&st);
                if(cpid<0)
                    perror("wait");
            }
            else
            {
                perror("fork");
            }
        }
        else if (fno == 9)
        {
            if ((strcmp(inp_cmd, "history --help") == 0))
            {
                printf("Display or manipulate the history list.");
            }
            else if (inparr[1]!=NULL&&strcmp(inparr[1], "-c") == 0)
            {
                for (int i = 0; i < 999; i++)
                {
                    strcpy(hist_list[i], "");
                }
                counter = 0;
            }
            else if (inparr[1]!=NULL&&strcmp(inparr[1], "-d") == 0)
            {
                if(inparr[2]==NULL || atoi(inparr[2])>counter)
                {
                    printf("incorrect arguments\n");
                }
                else{
                  strcpy(hist_list[atoi(inparr[2])-1],"");
                }
                
            }
            else
            {
                int ctr=0;
                for (int i = 0; i < counter; i++)
                {
                    if ((hist_list[i] != NULL) && strcmp(hist_list[i],"")!=0 )
                    {
                        printf("%d \t", ctr + 1);
                        printf("%s\n", hist_list[i]);
                        ctr++;
                    }
                }
            }
        }

        else if (fno == 10)
        {
            printf("%s", "[PROCESS COMPLETED....]\n");
            exit_status = 0;
            exit(EXIT_SUCCESS);
            break;
        }

        else
        { 
            printf("%s", "Error: Unrecognised Command\n");
        }
    }
        return 0;
    }
    

