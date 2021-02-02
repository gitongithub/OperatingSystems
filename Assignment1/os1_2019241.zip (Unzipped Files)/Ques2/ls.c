#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
static int cct;
char inpmp[10] = "";
int ctr=0;
char ftrf[10] = "";
void func();
char amt[1000] = "";
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        char *token = strtok(argv[1], " ");
        strcpy(inpmp, token);
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (token[0] != '-')
            {
                strcpy(amt, token);
            }
            else
            {
                strcpy(ftrf, token);
                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(amt, token);
                }              
            }
        }
    }
    func();
    return 1;
}
void func(){
    if (ftrf[1] == 'l')
    {
            struct passwd *tempf;
    struct group *getfd;
DIR *dictate;

    char buf[512];
    if (strlen(amt) == 0)
    {
        strcpy(amt,".");
    }
        dictate = opendir(amt);
        struct dirent *filter;
    struct stat tst;


    while ((filter = readdir(dictate)) != NULL)
    {
        if (filter->d_name[0] == '.')
        {
            continue;
        }
        sprintf(buf, "%s/%s", amt, filter->d_name);
        stat(buf, &tst);
        switch (tst.st_mode & S_IFMT)
        {
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;

        default:
            printf("-");
            break;
        }

        printf((tst.st_mode & S_IRUSR) ? "r" : "-");
        printf((tst.st_mode & S_IWUSR) ? "w" : "-");
        printf((tst.st_mode & S_IXUSR) ? "x" : "-");
        printf((tst.st_mode & S_IRGRP) ? "r" : "-");
        printf((tst.st_mode & S_IWGRP) ? "w" : "-");
        printf((tst.st_mode & S_IXGRP) ? "x" : "-");
        printf((tst.st_mode & S_IROTH) ? "r" : "-");
        printf((tst.st_mode & S_IWOTH) ? "w" : "-");
        printf((tst.st_mode & S_IXOTH) ? "x" : "-");
        tempf = getpwuid(tst.st_uid);
        getfd = getgrgid(tst.st_gid);
        printf(" %ld %s", tst.st_nlink, tempf->pw_name);
        printf(" %s %zu %s %s", getfd->gr_name, tst.st_size,filter->d_name,ctime(&tst.st_mtime));
    }
    closedir(dictate);
    }
    else if (ftrf[0] == '\0')
    {
     int n;
    struct dirent **nlist;

    if (strlen(amt) == 0)
    {
        n = scandir(".", &nlist, NULL, alphasort);
            if (n < 0)
    {
        perror("scan");
        exit(0);
    }
    }
    else
    {
        n = scandir(amt, &nlist, NULL, alphasort);
            if (n < 0)
    {
        perror("scan");
        exit(0);
    }
    }
    int i = 0;
    if (n < 0)
    {
        perror("scan");
    }
    else
    {
        do
        {
            printf("%s      ", nlist[i]->d_name);
            free(nlist[i++]);
        }while(i<n);
        printf("\n");
        free(nlist);
    }

    }
    else if (ftrf[1] == 'a')
    {
        int n;
            struct dirent **nlist;

    if (strlen(amt) == 0)
    {
        n = scandir(".", &nlist, NULL, alphasort);
            if (n < 0)
    {
        perror("scan");
        exit(0);
    }
    }
    else
    {
        n = scandir(amt, &nlist, NULL, alphasort);
            if (n < 0)
    {
        perror("scan");
        exit(0);
    }
    }
    int i = 0;
    if (n < 0)
    {
        perror("scan");
    }
    else
    {
        do
        {
            if (nlist[i]->d_name[0] == '.')
            {
                free(nlist[i++]);
                cct++;
                continue;
            }
            printf("%s ", nlist[i]->d_name);
            free(nlist[i++]);
        }while(i<n);
        printf("\n");
        free(nlist);
    }
    }
    else
    {
        printf("error");
        exit(0);
    }
    return;
}
