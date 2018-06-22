#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int mysys(const char *cmdstring)
{
	pid_t pid = 0;
	int status = 0;
	if(cmdstring == NULL)
	{
		printf("cmdstring is NULL\n");
		return -1;
	}
	
	if((pid = fork())<0)
	{
		printf("can not create chlid process\n");
		return -1;
	}
	if(pid == 0)
	{
		execl("/bin/sh","sh","-c",cmdstring,(char*)0);
		exit(0);
	}
	while(wait(&status)<0)
	{
		if(errno != EINTR)
		{
			printf("error\n");
			return -1;
		}
	}
	return 0;
}

int main()
{
	//test
	mysys("date");
	mysys("echo a b c");
	return 0;
}
