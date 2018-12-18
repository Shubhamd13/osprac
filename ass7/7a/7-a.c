#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Read characters from the pipe and echo them to stdout. */

void
read_from_pipe (int file,char arr[])
{
  FILE *stream;
  int c,i=0;
  stream = fdopen (file, "r");
  while ((c = fgetc (stream)) != EOF){
	    arr[i]=(char)c;
		i++;
	}
	arr[i]='\0';
  fclose (stream);
}

/* Write some random text to the pipe. */

void
write_to_pipe (int file,char *p)
{
  FILE *stream;
  stream = fdopen (file, "w");
  fprintf (stream, "%s",p);
  fclose (stream);
}

int
main (void)
{
  pid_t pid;
  int mypipe[2];
	int mypipe1[2];
	char arr[]="ramesh.txt";
  /* Create the pipe. */
  if (pipe (mypipe))
    {
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }
	if (pipe (mypipe1))
    {
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }


  /* Create the child process. */
  pid = fork ();
  if (pid == (pid_t) 0)
    {
	char filenam[100],rdf[100],c,i=0;
      /* This is the child process.
         Close other end first. */
      close (mypipe[1]);
      read_from_pipe (mypipe[0],filenam);
	close (mypipe[0]);
	close (mypipe1[0]);
	FILE* fl=fopen(filenam,"r");
	while ((c = fgetc (fl)) != EOF){
	    rdf[i]=(char)c;
		i++;
	}	
	rdf[i]='\0';
	write_to_pipe (mypipe1[1],rdf);
	close(mypipe1[1]);
      return EXIT_SUCCESS;
    }
  else if (pid < (pid_t) 0)
    {
      /* The fork failed. */
      fprintf (stderr, "Fork failed.\n");
      return EXIT_FAILURE;
    }
  else
    {
	char content[100];
      /* This is the parent process.
         Close other end first. */
      close (mypipe[0]);
      write_to_pipe (mypipe[1],arr);
	wait();
//-------------------------
	close (mypipe1[1]);
	read_from_pipe(mypipe1[0],content);
	printf("%s",content);
	close(mypipe1[0]); 
      return EXIT_SUCCESS;
    }
}
//---------OUTPUT------------------
/*
shubham@shubham:~/myos/ass7/7a$ gcc 7-a.c
7-a.c: In function ‘main’:
7-a.c:87:2: warning: implicit declaration of function ‘wait’; did you mean ‘main’? [-Wimplicit-function-declaration]
  wait();
  ^~~~
  main
shubham@shubham:~/myos/ass7/7a$ ./a.out
hi im ramesh
shubham@shubham:~/myos/ass7/7a$ 
*?

