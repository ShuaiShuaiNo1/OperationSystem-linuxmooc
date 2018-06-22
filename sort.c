#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int array[] = {1,10,2,9,3,8,4,7,5,6};
#define NR 10

void *worker(void *arg)
{
	int temp,i,j,index;
	for(i=0;i<NR/2;i++)
	{
		index = i;
		for(j = i+1;j<NR/2;j++)
		{
			if(array[j]<array[index])
				index = j;
		}
		if(index != i)
		{
			temp = array[i];array[i] = array[index]; array[index] = temp;
		}	
	}
	
}

void master()
{
	int temp,i,j,index;
	for(i=NR/2;i<NR;i++)
	{
		index = i;
		for(j = i+1;j<NR;j++)
		{
			if(array[j]<array[index])
				index = j;
		}
		if(index !=i)
		{
			temp = array[i];array[i] = array[index];array[index] = temp;
		}
	}
}

int main()
{
	pthread_t worker_tid;
	int i,j,k;
	pthread_create(&worker_tid,NULL,worker,NULL);
	master();
	pthread_join(worker_tid,NULL);
	
	int *a = (int *)malloc(sizeof(int)*(NR/2));
	int *b = (int *)malloc(sizeof(int)*(NR/2));
	for(i=0;i<NR/2;i++) a[i] = array[i];
	for(i=NR/2;i<NR;i++) b[i - NR/2] = array[i];
	i = 0;j = 0;k = 0;
	while(i < NR/2 && j < NR/2)
	{
		if(a[i]<b[j])
			array[k++] = a[i++];
		else
			array[k++] = b[j++];
	}
	while(i<NR/2)
		array[k++] = a[i++];
	while(j<NR/2)
		array[k++] = b[j++];
	
	for(i = 0;i<NR;i++)
		printf("%d ",array[i]);
	printf("\n");
	return 0;
}


