#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    char flag[10] = "";
    char fileName[1000];
    if(strcmp(argv[1],"rm")==0){
        printf("less arguments\n");
        exit(0);
    }
    char *token = strtok(argv[1], " ");
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flag, token);
        token = strtok(NULL, " ");
    }
    while (token != NULL)
    {
        strcpy(fileName, token);
        if (strcmp(flag, "") == 0)
        {
                int file = open(fileName, O_RDONLY);
                if (file < 0)
                {
                    perror(fileName);
                    token = strtok(NULL, " ");
                    continue;
                }
                char ch;
                while (read(file, &ch, 1))
                {
                    write(STDIN_FILENO, &ch, 1);
                }
                printf("\n");
                close(file);
        }
        else if (flag[1] == 'E')
        {
            int file = open(fileName, O_RDONLY);
            if (file < 0)
            {
                perror(fileName);
                token = strtok(NULL, " ");
                continue;
             }
            char ch;
            while (read(file, &ch, 1))
            {
                if (ch == '\n')
                {
                    char c = '$';
                    write(STDIN_FILENO, &c, 1);
                }
                write(STDIN_FILENO, &ch, 1);
            }
            printf("\n");
            close(file);
        }
        else if (flag[1] == 'T')
        {
            int file = open(fileName, O_RDONLY);
            if (file < 0)
            {
                perror(fileName);
                token = strtok(NULL, " ");
                continue;
            }
            char ch;
    
            while (read(file, &ch, 1))
            {
                if (ch == 9)
                {
                    char c = '^',c1='I';
                    write(STDIN_FILENO, &c, 1);
                    write(STDIN_FILENO, &c1, 1);
                }
                else{
                    write(STDIN_FILENO, &ch, 1);
                }
            }
            printf("\n");
            close(file);
        }
        else{
            printf("invalid command\n");
            exit(0);
        }
        token = strtok(NULL, " ");
    }
    return 0;
}