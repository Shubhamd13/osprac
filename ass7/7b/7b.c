/*
7b. FIFOs: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts
number of characters, number of words and number of lines in accepted sentences, writes this
output in a text file and writes the contents of the file on second pipe to be read by first process
and displays on standard output.
*/
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
int main(){
	int i,fd1,fd2;
	char str[100],str1[400];
	mkfifo("fifofile1",0666);
	mkfifo("fifofile2",0666);
	fd1=open("fifofile1",O_RDWR);
		printf("Enter a string:");
		gets(str);
		write(fd1,str,sizeof(str));
	close(fd1);
	fd2=open("fifofile2",O_RDWR);
	read(fd2,str1,sizeof(str1));
	printf("%s",str1);
	
	close(fd2);
}
