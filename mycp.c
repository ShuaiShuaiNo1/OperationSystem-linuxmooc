#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	int fd1,fd2;
	fd1 = open(argv[1],O_RDONLY);
	if(fd1 != -1)
		printf("fd1 open suc\n");
	char buf[1024];
	int count;
	count = read(fd1,buf,sizeof(buf));

	buf[count] = 0;
	
	fd2 = open(argv[2],O_WRONLY);
	if(fd2 != -1)
		printf("fd2 open suc\n");

	count = write(fd2,buf,count),

	close(fd1);
	close(fd2);
	return 0;
}
