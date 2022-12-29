/* Write a program to implement the shell. It should display the command
 prompt “myshell$”. Tokenize the command line and execute the given
 command by creating the child process. Additionally it should interpret the
 following commands.
 myshell$ search a filename pattern :- To search all the occurrence of
 pattern in the file.
 myshell$ search c filename pattern :- To count the number of occurrence
 of pattern in the file. */


 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>	// open,read(),close() : file related function
void search(char *p1,char *pat,char*fname)
{
	int handle,i=0,cnt=0;
	char ch,data[100],*ptr;
	
	handle=open(fname,O_RDONLY);
	
	if(handle==-1)
	{
		printf("\n File %s Not Found....",fname);
	}
	else
	{
		if(strcmp(p1,"F")==0)
		{	
			i=0;
			while(read(handle,&ch,1))			//on failure read() function returns 0
			{
				data[i]=ch;
				i++;
				if(ch=='\n')
				{
					data[i]='\0';
					if(strstr(data,pat)!=NULL)
					{
						printf("\nFIRST OCCURANCE OF PATTERN IN LINE IS GIVEN BELOW\n");
						puts(data);
						break;
					}
					i=0;
				}
			}
			close(handle);
		}
		else if(strcmp(p1,"C")==0)
		{
			cnt=0;
			i=0;
                        while(read(handle,&ch,1))                       //on failure read() function returns 0
                        {
                                data[i]=ch;
                                i++;
                                if(ch=='\n')
                                {
                                        data[i]='\0';
                                        ptr=data;
                                        while((ptr=strstr(ptr,pat))!=NULL)
                                        {
					                     	cnt++;
						                    ptr++;
                                        }
	
					                    i=0;
                                }
                        }
			printf("\nNo of occurances of '%s' = %d",pat,cnt);
                        close(handle);
		}
		else if(strcmp(p1,"A")==0)
		{
			 printf("\nDispaying All Occurances of '%s'\n",pat);
                        i=0;
                        while(read(handle,&ch,1))                       //on failure read() function returns 0
                        {
                                data[i]=ch;
                                i++;
                                if(ch=='\n')
                                {
                                        data[i]='\0';
                                        
                                        if((ptr=strstr(data,pat))!=NULL)
                                        {
                                                puts(data);
                                                
                                        }
					i=0;
                                }
                        }
		}

	}//else
	
	
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
                                if(fork()==0)
                                {
                                       	execlp(tok1,tok1,tok2,tok3,NULL);
                                }
                                wait(0);
                                break;
                        case 4 :
				if(strcmp(tok1,"search")==0)
				{
					search(tok2,tok3,tok4);
				}
				else
				{
                                	if(fork()==0)
                                	{
                                        	execlp(tok1,tok1,tok2,tok3,tok4,NULL);
                                	}
                                	wait(0);
				}
                                break;

                }
        }


}