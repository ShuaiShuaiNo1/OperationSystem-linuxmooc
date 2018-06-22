#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_DIR_NAME 1024
#define MAX_CMD 128

int parseline(char *buf,char ** argv)
{
	while(*buf==' ')
	{
		buf++;
 	}
	int delim = 0;
	int argc = 0;
	while(*buf != '\n')
	{
		while(buf[delim] != '\n' && buf[delim] != ' ')
		{
			delim++;
 		}
		if(buf[delim] == '\n')
 		{
			buf[delim] = '\0';
			argv[argc++] = buf;
			break;
		}
		buf[delim] = '\0';
		argv[argc++] = buf;

		buf += delim +1;
		delim = 0;
		while(*buf == ' ')
		{
			buf++;
 		}
  	}
	
  	argv[argc] = NULL;
	return argc;
}
int buildin_command(char **argv)
{
	if(strcmp(argv[0],"exit")==0)
  	{
		exit(0);
 	}
	if(strcmp(argv[0],"cd")==0)
  	{
		if(chdir(argv[1]))//chdir:change currently working catalog
			printf("myselous:cd:%s:no such directory\n",argv[1]);
		return 1;
 	}
	if(strcmp(argv[0],"pwd")==0)
  	{
		char buf[MAX_DIR_NAME];
		printf("%s\n",getcwd(buf,sizeof(buf)));//copy current working path to first parameter.
		return 1;
 	}
	return 0;
	
}
void eval(char * cmdstring)
{
	char * argv[MAX_CMD];
	char buf[MAX_CMD];
	int flag = 0,k,argc = 0;
	strcpy(buf,cmdstring);
	argc = parseline(buf,argv); 
	if(argv[0] == NULL)
  	{
		return;
 	}
	if(buildin_command(argv))return;
	int pid = fork();
	if(pid == 0)
 	{
		for(k=0;k<argc;k++)
 		{
			if(strcmp(argv[k],">")==0)
			{
				char *filename = argv[k+1];
				argv[k] = NULL;
				//printf("%s\n",filename);
				close(1);
				int fd = open(filename,O_WRONLY|O_CREAT);
                ftruncate(fd,0);				
  			}
 		}
		if(execvp(argv[0],argv)<0)
  		{
			fflush(stdout);
			printf("%s:command not fount.\n",argv[0]);
			exit(0);
 		}
  	} 
	wait(NULL);
}

int main(int argc,char * argv[])
{
	char cmdstring[MAX_CMD];
	int n;
	while(1)
	{
		printf("myshell>");
		fflush(stdout);

		if((n = read(0,cmdstring,MAX_CMD))<0)
		{
			printf("read error\n");
 		}
  		eval(cmdstring);
 	}
	return 0;
}
