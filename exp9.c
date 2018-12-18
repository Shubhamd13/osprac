#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
int main()
{
	int ch,fd,fd1,flag=0,flag1 = 0,flag2=0,ch1;
	char ans,str[100],str1[20];
	struct stat sbuf;

	do
	{
		printf("\n\t*** MENU ***\n");	
		printf("\n1.Create");
		printf("\n2.Open");
		printf("\n3.Read");
		printf("\n4.Write");
		printf("\n5.Lseek");
		printf("\n6.Fstat");
		printf("\n7.Close");

		printf("\nEnter ur choice :: ");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1://create
			printf("\nENTER FILENAME : ");
			scanf("%s",&str1);
			fd = creat(str1,00700);
			if(fd == -1)
				printf("\nFILE IS NOT CREATED!!!");
			else
			{
				printf("\nFILE IS CREATED SUCCESSFULLY!!!");
				flag = 1;
			}
			
			break;

			case 2://open
			printf("\nIN WHICH MODE U WANT TO OPEN THE FILE ?\n1.READ\n2.WRITE\nENTER CHOICE:");	
			scanf("%d",&ch1);
			if(ch1 == 1)
			{
				fd = open(str1,0);
				flag1 = 1;
				printf("\nFILE IS OPENED INTO THE READ MODE!!! ");
			}
			if(ch1 == 2)
                        {
                                fd = open(str1,1);
                                flag2 = 1;
                                printf("\nFILE IS OPENED INTO THE WRITE MODE!!! ");
                        }
			if(ch1 != 1 && ch1 != 2)
				printf("\nINVALID CHOICE!!");

			break;

			case 3://read
			if(flag1 == 1)
			{
				lseek(fd,0,SEEK_SET);
				printf("\nREADING FROM FILE:");
				while(read(fd,&str,1))
					printf("%c",*str);				
			}
			else
				printf("\nPLEASE OPEN FILE IN READ MODE!!");
			break;

			case 4://write
			if(flag2 == 1)
			{
				lseek(fd,0,SEEK_END);
				printf("\nENTER THE DATA TO WRITE INTO THE FILE:");
				printf("\n\nEND CONDITIION IS '#'");
				while(*str != '#')
				{
					scanf("%s",&str);
					if (*str != '#')
					{
					        write(fd,str,strlen(str));
						write(fd," ",strlen(" "));
					}
				}
			}
			else
				printf("\nPLEASE OPEN FILE IN WRITE MODE!!");
			break;

			case 5://lseek
				lseek(fd,0,SEEK_SET);
				printf("\nFILE POINTER IS AT START OF FILE!!");
				lseek(fd,0,SEEK_END);
				printf("\nFILE POINTER IS AT END OF FILE!!");
			break;

			case 6://fstat
			fstat(fd,&sbuf);
			printf("\nSTATUS OF FILE: %s",str1);
			printf("\n\nINODE NO.:%d",sbuf.st_ino);
			printf("\nUID : %d ",sbuf.st_uid);
			printf("\nGID : \%d ",sbuf.st_gid);
			printf("\nTYPE OF PERMISSION : %o",sbuf.st_mode);
			printf("\nNUMBER OF LINKS : %d",sbuf.st_nlink);
			printf("\nSIZE OF BYTES : %d",sbuf.st_size);
			printf("\nBLOCK ALLOCATED : %d",sbuf.st_blocks);
			printf("\nLast status change:       %s", ctime(&sbuf.st_ctime));
           printf("Last file access:         %s", ctime(&sbuf.st_atime));
           printf("Last file modification:   %s", ctime(&sbuf.st_mtime));


			break;	

			case 7://close
				close(fd);
				printf("\nFILE IS CLOSED SUCCESSFULLY!!!");
			break;		
			
			default:
				printf("\n\nINVALID CHOICE!!");

		}
		printf("\nDo u want to continue?(y/n)");
		scanf("%s",&ans);
	}while(ans=='y'); 
	return(0);
}

