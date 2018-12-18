/*
Assignment No. 6: Deadlock Avoidance Using Semaphores: Implement the deadlock-free solution to Dining
Philosophers problem to illustrate the problem of deadlock and/or starvation that can occur when many
synchronized threads are competing for limited resources.
*/

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t frk[5];
void * philosopher(void *p){
	int b,a,i=*((int *)p);
	while(1){
		printf("Philosopher %d is thinking\n",i);
		int slee=rand()%3;
		sleep(slee);
		printf("Philosopher %d is hungry\n",i);
		if(i==4){
			sem_wait(&frk[(i+1)%5]);
			sem_wait(&frk[i]);
		}else{
			sem_wait(&frk[i]);
			sem_wait(&frk[(i+1)%5]);
		} 
		printf("Philosopher %d is eating\n",i);
		sleep(slee);
		sem_post(&frk[i]);
		sem_post(&frk[(i+1)%5]);
	}
}
int main(){
	int i,arr[5];
	for(i=0;i<5;i++)
		sem_init(&frk[i],0,1);
	pthread_t ph[5];
	for(i=0;i<5;i++){
		arr[i]=i;
		pthread_create(&ph[i],NULL,philosopher,&arr[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(ph[i],NULL);
}
