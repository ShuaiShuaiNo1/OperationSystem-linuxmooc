#include <sys/types.h>//open system need
#include <sys/stat.h>//open system need
#include <fcntl.h>//open system need
#include <unistd.h>//read/write need
int main(int argc, char * argv[])
{
	int fd;
	fd = open(argv[1],O_RDONLY);	
	char buf[1024];
	int count;
	count = read(fd,buf,sizeof(buf));

	buf[count] = 0;
	puts(buf);

	close(fd);
	return 0;
}
