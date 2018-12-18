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
	int fd1,fd2,i=0;
	FILE *fp;
	int line,words,c;
	line=words=c=0;
	char str[100],ch,contents[400];
	mkfifo("fifofile1",0666);
	mkfifo("fifofile2",0666);
	fd1=open("fifofile1",O_RDWR);
	read(fd1,str,sizeof(str));
	close(fd1);
	printf("%s",str);
	while(str[i]!='\0')
  	{
  		 if(str[i]==' ' || str[i]=='.')
	  	 {
			words++;
			if(str[i]=='.')
			    line++;
	   	 }
		 else
			c++;
   		i++;
	  }
	  printf("\n total characters=%d",c);
 	 printf("\n total words=%d\n",words);
	  printf("\n total lines=%d\n",line);
	  fp=fopen("te.txt","w+");
	//printf("\n%d\n",fp);
	fprintf(fp,"\n total characters=%d",c);
	fprintf(fp,"\n total words=%d\n",words);
	fprintf(fp,"\n total lines=%d\n",line);
	fseek(fp,0,SEEK_SET);
	i=0;
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		contents[i]=ch;
		i++;
	}
	fclose(fp);
	
	fd2=open("fifofile2",O_RDWR);
	write(fd2,contents,sizeof(contents));	
	close(fd2);
}
