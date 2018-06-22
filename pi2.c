#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NR_TOTAL 1000000
#define NR_CPU 4
#define NR_CHILD (NR_TOTAL/NR_CPU)

struct param {
	int start;
	int end;
};
struct result{
	double sum;
};

void *compute(void *arg)
{
	struct param *param;
	struct result *result;
	double sum = 0,zf;
	int i;

	param = (struct param *)arg;
	for( i = param->start; i < param->end; i++)
	{
		if(i%2==0) zf = 1; else zf = -1;
		sum += zf/(2*i+1);	
	}
	
	result = malloc(sizeof(struct result));
	result->sum = sum;
	return result;
}

int main()
{
	pthread_t workers[NR_CPU];
	struct param params[NR_CPU];
	int i;
	for (i=0;i< NR_CPU;i++)
	{
		struct param *param;
		param = &params[i];
		param->start = i*NR_CHILD;
		param->end = (i+1)*NR_CHILD;
		pthread_create(&workers[i],NULL,compute,param);
	}
	double sum = 0;
	for(i = 0;i<NR_CPU;i++)
	{
		struct result *result;
		pthread_join(workers[i],(void **)&result);
		//printf("result->sum:%f\n",result->sum);
		sum += result->sum;
		free(result);
	}

	printf("sum = %f\n", sum*4);
	return 0;
}

