/*
Assignment No. 8:Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment and
writes the message to the shared memory segment. Client process reads the message from the shared
memory segment and displays it to the screen.

terminal-> ipcs -m
*/
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
	if(shmid<0){
		printf("error\n");
		exit(0);
	}else{
		printf("shmid=%d\n",shmid);
		p=(buffer*)shmat(shmid,NULL,0);
		p->length=0;
		while(1)
		if(p->length==0)
		{
		printf("\nenter the text\n");
		gets(arr);
		p->length=strlen(arr);
		strcpy(p->arr,arr);
		}			
	}
	
}
