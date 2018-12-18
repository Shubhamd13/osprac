#include<stdio.h>
#define MAX 20

int bsearch(int a[MAX],int f,int l,int s);

int main(int argc,char *argv[])
{
	int i,s,f;
	int a[MAX];
	
	for(i=0;i<argc;i++)
		a[i]=atoi(argv[i]);

	printf("\nThe sorted array is : \n");

	for(i=0;i<argc;i++)
		printf("%d\t",a[i]);

	printf("\nEnter element to be searched : ");
	scanf("%d",&s);

	f=bsearch(a,0,argc-1,s);
	printf("\n");
	if(f!=-1)
		printf("The element %d found at %d location..!!",s,f+1);
	else
		printf("The element %d is not present in the list..!!",s);
		
	printf("\n");

	return 0;
}

int bsearch(int a[MAX],int f,int l,int s)
{
	int mid;
	while(f<=l)
	{
		mid=(f+l)/2;
		if(s==a[mid])
			return(mid);
		else if(s<a[mid])
			l=mid-1;
		else
			f=mid+1;
	}
	return -1;
}
