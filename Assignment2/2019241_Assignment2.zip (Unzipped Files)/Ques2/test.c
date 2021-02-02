#include<stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#define  sys_sh_task_info 335
int main(int argc, char **argv)
{
  int pid_inp,s1;
  char fpath[256];
  s1=printf("Enter pid value:");
	if(s1==-1)
	{
		perror("Erro is");
	}
  scanf("%d",&pid_inp);
	int s2;
	if(s2==-1)
	{
		perror("Erro is");
	}
  printf("Enter file path:");
	int s3;
	if(s3==-1)
	{
		perror("Erro is");
	}
  scanf("%s",fpath);
	int s4;
	if(s4==-1)
	{
		perror("Erro is");
	}
  printf("%s\n",fpath);
	int s5;
	if(s5==-1)
	{
		perror("Erro is");
	}
  long int chk = syscall(sys_sh_task_info, pid_inp,fpath);
  printf("System call sys_sh_task_info returned %ld. Check Kernel Logs\n", chk);
  return 0;
}
