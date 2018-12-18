#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void printArr(int [],int );
int partition (int [], int , int );
void quickSort(int [], int , int ,int );
void bubbleSort(int [],int);
void main()
{
    	int arr[20],n,i;

	printf("Enter the no. of elements:-\n");
    	scanf("%d",&n);
    	printf("Enter the elements:-\n");
    	for(i=0;i<n;i++)
    		scanf("%d",&arr[i]);
	pid_t pid;
	pid=fork();
	printf("\nThe process Id is:%d\n",getpid());
		switch(pid)
		{
			case -1: printf("Error has occured in creating child process..");
					break;
			case 0:	printf("We are in child process!!\n");
					quickSort( arr, 0, n - 1, n );
					printf("\nSorted Elements:\n");
					printArr(arr,n);
					break;
			default:        wait();
                                        printf("we are in parent process!!\n");
					bubbleSort( arr,  n );
					break;
		}
}


void printArr( int arr[], int n )
{
    	int i;
    	for ( i = 0; i < n; ++i )
    	    printf( "%d ", arr[i] );
	printf("\n");
}
 
/* This function is same in both iterative and recursive*/
int partition (int arr[], int l, int h)
{
    	int i, temp,j, pivot;

	pivot = arr[l];		//set the lowest index element as pivot
	i = l + 1;		
	j=h;
	while(i<=j)
	{
		while(arr[i]<=pivot)
			i++;
		while(arr[j]>pivot)
			j--;
		if(i<=j)
		{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			i++;
			j--;
		}
	}
	arr[l]=arr[j];
	arr[j]=pivot;
	return j;

}
   
 
 

void quickSort(int arr[], int l, int h,int n)
{
	int p;
	static int pass=1;    
	if (l < h)
    	{        
        	p = partition(arr, l, h); 
		printf("After Pass %d : ",pass++);
			printArr( arr, n );
        	quickSort(arr, l, p - 1, n);  
        	quickSort(arr, p + 1, h, n);
    	}
}

void bubbleSort(int arr[],int n)
{
	int c,d,swap;
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d <(n - c - 1); d++)
    {
      if (arr[d] > arr[d+1]) 
      {
        swap       = arr[d];
        arr[d]   = arr[d+1];
        arr[d+1] = swap;
      }
    }
  }
 
  printf("Sorted list in ascending order:\n");
 
  for ( c = 0 ; c < n ; c++ )
     printf("%d ", arr[c]);
 
 
}


