/*Assignment No. 4: Thread synchronization using counting semaphores. Application to demonstrate:
producer-consumer problem with counting semaphores and mutex.
*/
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define MAX 20
#define BUFF 10
char avbuff[BUFF];
sem_t empty,full;
pthread_mutex_t mutex;
int index=0;
void *produce(void *arg)
{
		int slptm=rand()%4;
		sleep(slptm);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex); 
		avbuff[index]=rand()%10;
		printf("Item produced is %d \n",avbuff[index]);
		index++;
		pthread_mutex_unlock(&mutex); 
		sem_post(&full);
		pthread_exit(NULL);
}

void *consumer(void *arg)
{
		int slptm=rand()%4;
		sleep(slptm);
		sem_wait(&full);
		pthread_mutex_lock(&mutex); 
		int j=avbuff[--index];
		printf("Item consumed is %d \n",j);
		pthread_mutex_unlock(&mutex); 
		sem_post(&empty);
		pthread_exit(NULL);
} 

int main() 
{ 
	int i,p=0,c=0;
	pthread_t ptid[MAX],ctid[MAX]; 
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty,0,BUFF); 
	sem_init(&full,0,0); 
	//---------------------------------------------
	do{
		printf("Enter number of producers:");
		scanf("%d",&p);
	}while(p>MAX);
	do{
		printf("Enter number of consumers:");
		scanf("%d",&c);
	}while(c>MAX);
	//----------------------------------------------
	for(i=0;i<p;i++)
		pthread_create(&ptid[i],NULL,produce,NULL);
	for(i=0;i<c;i++)
		pthread_create(&ctid[i],NULL,consumer,NULL);	 
	//----------------------------------------------
	for(i=0;i<p;i++)
		pthread_join(ptid[i],NULL); 
	for(i=0;i<c;i++)	 
		pthread_join(ctid[i],NULL); 
	return 0;
} 


