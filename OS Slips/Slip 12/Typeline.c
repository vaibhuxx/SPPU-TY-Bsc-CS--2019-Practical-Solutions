/*Write a C program to implement the shell which displays the command
prompt “myshell$”. It accepts the command, tokenize the command line and
execute it by creating the child process. Also implement the additional
command ‘typeline’ as
typeline +n filename
:- To print first n lines in the file.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>	// open,read(),close() : file related function

void typeline(char *p1,char*fname)
{
	int handle,n,lcnt;
	char ch;
	
	handle=open(fname,O_RDONLY);
	
	if(handle==-1)
	{
		printf("\n File %s Not Found....",fname);
	}
	else
	{
		
		if(strcmp(p1,"a")==0)
		{
			/* Displaying All contents of file */
			printf("\nContents of FILE=%s\n",fname);
			while(read(handle,&ch,1))			//on failure read() function returns 0
			{
				printf("%c",ch);
			}
			close(handle);
		}
		else			//else means parameter is either +n or -n
		{
			n=atoi(p1);
			lcnt=0;
			if(n>0)
			{
				printf("Displaying First %d lines of file\n",n);
				while(read(handle,&ch,1))
				{
					printf("%c",ch);
					if(ch=='\n')
						lcnt++;
					if(lcnt==n)
						break;
				}
				close(handle);
			}
			else
			{
				n=-n;
				printf("Displaying Last %d lines of file\n",n);
                                while(read(handle,&ch,1))
                                {
                                       if(ch=='\n')
                                                lcnt++;
                                }
				
				n=lcnt-n;
				lcnt=0;
				lseek(handle,0,SEEK_SET);	//starting from start of file again
				while(read(handle,&ch,1))
                                {
                                         if(ch=='\n')
                                                lcnt++;
                                        if(lcnt==n)
                                                break;
                                }
				while(read(handle,&ch,1))
                                {
                                        printf("%c",ch);
                                }
				close(handle);
			}
		} 
	}
	
	
}
int main()
{
        char cmd[80],tok1[10],tok2[10],tok3[10],tok4[10];
        int n;
        while(1)
        {
                printf("\nMYSHELL $]");

                fgets(cmd,80,stdin);

                n=sscanf(cmd,"%s%s%s%s",tok1,tok2,tok3,tok4);   //n=no of tokens are formed from given command

                switch(n)
                {
                        case 1:

                                if(fork()==0)
                                {
                                        execlp(tok1,tok1,NULL); //paramenters- nameOfProcess,parametersOfProcess        
                                }
                                wait(0);
                                break;
                        case 2 :
                                if(fork()==0)
                                {
                                        execlp(tok1,tok1,tok2,NULL);
                                }
                                wait(0);
                                break;
                        case 3:
				if(strcmp(tok1,"typeline")==0)
				{
					typeline(tok2,tok3);
				}
				else
				{
                                	if(fork()==0)
                                	{
                                        execlp(tok1,tok1,tok2,tok3,NULL);
                                	}
                                	wait(0);
				}
                                break;
                        case 4 :
                                if(fork()==0)
                                {
                                        execlp(tok1,tok1,tok2,tok3,tok4,NULL);
                                }
                                wait(0);
                                break;

                }
        }


}

/*					OUTPUT
 * [shalmali@localhost SHELL]$ ./a.out
 *
 * MYSHELL $]typeline -2 a.txt
 * Displaying Last 2 lines of file
 * we are in tybcs.
 * we are programmer.
 *
 * MYSHELL $]typeline 2 a.txt
 * Displaying First 2 lines of file
 * India is my country.
 * I love my india.
 *
 * MYSHELL $]typeline a a.txt
 *
 * Contents of FILE=a.txt
 * India is my country.
 * I love my india.
 * we are computer students from india.
 * we are in tybcs.
 * we are programmer.
 *
 * MYSHELL $]^C
 * [shalmali@localhost SHELL]$ 
 *
 * */