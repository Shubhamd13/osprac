//Q3.Implement multithreading for Matrix Multiplication using pthreads
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
int r[2],c[2];
int *m[3];
//---------------------------------
void* singlecell(void *p){
	int row,col,k,res;
	int *arr;
	arr=(int *)p;
	row=arr[0];
	col=arr[1];
	res=0;
	for(k=0;k<c[0];k++){
	res+=m[0][row*c[0]+k]*m[1][k*c[1]+col];
	}
	m[2][row*c[1]+col]=res;
	sleep(10);
	pthread_exit(NULL);
}
int main(){
	printf("%d",getpid());
	int i,j,k;
	do{
	printf("Enter dimensions of Matrix1:");
	scanf("%d %d",&r[0],&c[0]);
	printf("Enter dimensions of Matrix2:");
	scanf("%d %d",&r[1],&c[1]);
	}while(r[1]!=c[0]);

	for(k=0;k<2;k++){
		m[k]=(int *)malloc(r[k]*c[k]*sizeof(int));
		printf("Enter values for Matrix%d:\n",k+1);
		for(i=0;i<r[k];i++)
			for(j=0;j<c[k];j++)
				scanf("%d",&(m[k][i*c[k]+j]));
		printf("Entered values:\n");
		for(i=0;i<r[k];i++){
			for(j=0;j<c[k];j++){
				printf("%d ",m[k][i*c[k]+j]);
			}
		printf("\n");
		}
	}
	m[2]=(int *)malloc(r[0]*c[1]*sizeof(int));
	pthread_t tid[r[0]*c[1]];
	int arr[r[0]*c[1]][2];
	for(i=0;i<r[0];i++)
		for(j=0;j<c[1];j++){
			arr[i*c[1]+j][0]=i;
			arr[i*c[1]+j][1]=j;
			pthread_create(&tid[i*c[1]+j],NULL,singlecell,arr[i*c[1]+j]);
		}
	for(i=0;i<(r[0]*c[1]);i++){
		pthread_join(tid[i],NULL);
	}
	printf("Result values:\n");
	for(i=0;i<r[0];i++){
		for(j=0;j<c[1];j++){
			printf("%d ",m[2][i*c[1]+j]);
			}
		printf("\n");
		}
}

