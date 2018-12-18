/*
Assignment No. 5: Thread synchronization and mutual exclusion using mutex. Application to demonstrate:
Reader-wrtier problem with reader priority.
*/
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 100
int readCount=0,number=0;
sem_t mutex,wrtie;

void* reader(void *p){
	int slptm=rand()%5;
	sleep(slptm);
	sem_wait(&mutex);
	readCount++;
	if(readCount==1)
		sem_wait(&wrtie); //the first reader will be the leader who stops the writer;
	sem_post(&mutex);
	printf("Reader read %d\n",number);
	sem_wait(&mutex);
	readCount--;
	if(readCount==0)
		sem_post(&wrtie); //the leader goes and ensures that the writer is free to write
	sem_post(&mutex);
	
}
void* writer(void *p){
	int slptm=rand()%5;
	sleep(slptm);
	sem_wait(&wrtie);
	number=rand()%100;
	printf("writer wrote %d\n",number);
	sem_post(&wrtie);
}

int main(){
	int i,num_rt,num_wt;
	pthread_t tid_rt[MAX],tid_wt[MAX]; 
	sem_init(&mutex,0,1);
	sem_init(&wrtie,0,1);
	do{
		printf("Enter no. of readers:");
		scanf("%d",&num_rt);
	}while(num_rt> MAX );
	do{
		printf("Enter no. of wrtiers:");
		scanf("%d",&num_wt);
	}while(num_wt> MAX );
	for(i=0;i<num_rt;i++)
		pthread_create(&tid_rt[i],NULL,reader,NULL);
	for(i=0;i<num_wt;i++)
		pthread_create(&tid_wt[i],NULL,writer,NULL);
	//---------------------------------------------------
	for(i=0;i<num_wt;i++)
		pthread_join(tid_wt[i],NULL);
	for(i=0;i<num_rt;i++)
		pthread_join(tid_rt[i],NULL);
}
