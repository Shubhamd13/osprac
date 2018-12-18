#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdio.h>
#define SIZE 400
typedef struct buffer{
	int length;
	char arr[100];
}buffer;
int main(){
	char arr[100];
	key_t key;
	key = 1234;
	int shmid;
	buffer *p;
	shmid=shmget(key,SIZE,IPC_CREAT|0666);
	p=(buffer*)shmat(shmid,NULL,0);
	while(1)
	if(p->length!=0)
	{
	strcpy(arr,p->arr);
	printf("\n%s\n",arr);
	p->length=0;
	}
}
