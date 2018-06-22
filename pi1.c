#include <stdio.h>
#include <pthread.h>
#define NR 1000000 

double worker_output = 0;
void *worker(void *arg)
{
	int i;
	double zf;
	for(i=NR /2; i<NR; i++)
	{
		if(i%2 == 0) zf = 1;else zf = -1;
		worker_output += zf/(2*i+1);
		//printf("i:%d zf:%f worker temp:%f\n",i,zf,zf/(2*i+1));
 	}
	return NULL;
}

double master_output = 0;

void master()
{
	int i;
	double zf;
	for(i = 0;i<NR/2;i++)
	{
		if(i%2 == 0) zf = 1;else zf = -1;
		master_output += zf/(2*i+1);
		//printf("i:%d zf:%f master temp:%f\n",i,zf,zf/(2*i+1));
  	}

}
int main()
{
	pthread_t worker_tid;
	double total = 0;

	pthread_create(&worker_tid,NULL,worker,NULL);
	master();
	pthread_join(worker_tid,NULL);
	//printf("master: %f,worker: %f\n",master_output,worker_output);
	total = master_output + worker_output;
	printf("PI= %f\n",total*4);
	return 0;
}
