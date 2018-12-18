#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<sys/types.h>
void bubble_sort(int , int []);                                                               
int main()		                                                      
{   
	char str[100],*str1[30];
	int i,n,size,arr[30];                          
	printf("Enter total no. of elements : ");
 	scanf("%d",&size);
 	printf("Enter the array\n ");
	for(i=0; i<size; i++){
 	 	printf("Enter %d element : ",i+1);
 		scanf("%d",&arr[i]);
	}                                                                              
	bubble_sort(size, arr);                                        
	printf("after sorting\n");                                
	for(i=0;i<30;i++)
		str1[i]=NULL;
	for(i=0;i<size;i++)
		{
			sprintf(str,"%d",arr[i]);
			str1[i]=strdup(str);
			//printf("%s\n",str1[i]);
		}     
       	printf("\n");
	pthread_t pid=fork();
	switch(pid){
		case -1:
			exit(0);
			break;
		case 0:
			execve("binary",str1,NULL);  
			break;
		default:
			wait(NULL);
	}
return 0;
}                                                       
   void bubble_sort(int m, int arr[])
   {                                                           
       int i,j,t;                                            
                                                               
       for(i=1;i<= m-1;i++)                               
          for(j=1;j<=m-i;j++)                             
             if(arr[j-1]>=arr[j])                                
             {
                t =arr[j-1];                                    
                arr[j-1]=arr[j];                                 
                arr[j] = t;                                      
             }                                                 
   }  


