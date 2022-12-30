#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>	//opendir(),readdir(),closedir()
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>	// open,read(),close() : file related function
void list(char *p1,char*dname)
{
	DIR *dir;
	struct dirent *entry;		//used to hold entry of directory i.e file or dir
	struct stat info;		//hold inforrmation about file i.e inode, regular file
	int cnt=0;
 
	dir=opendir(dname);		
	if(dir==NULL)
	{
		printf("\n Directory %s Not Found....",dname);
	}
	else
	{
		if(strcmp(p1,"F")==0)
		{
			while((entry=readdir(dir))!=NULL)
			{
				stat(entry->d_name,&info);
				if(info.st_mode & S_IFREG)	//s_mode =2 is for regular file regular file
					printf("%s\n",entry->d_name);
			}
		}
		else if(strcmp(p1,"N")==0)
		{
			cnt=0;
			while((entry=readdir(dir))!=NULL)
                        {
				cnt++;
                        }
			printf("\nTotal no. of entries in directory '%s' = %d ",dname,cnt);
		}
		else if(strcmp(p1,"I")==0)
		{
			while((entry=readdir(dir))!=NULL)
                        {
                                stat(entry->d_name,&info);
                                if(info.st_mode & S_IFREG)      //s_mode =2 is for regular file regular file
                                {
				        printf("File name =%s\t",entry->d_name);
					printf("Inode=%d\n",info.st_ino);
				}
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
				if(strcmp(tok1,"list")==0)
				{
					list(tok2,tok3);
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
/*			OUTPUT
 *	[shalmali@localhost SHELL]$ ./a.out
 *      [shalmali@localhost SHELL]$ ./a.out
 *
 *      MYSHELL $]list I .
 *      File name =seta2.c	Inode=73504
 *      File name =seta3.c	Inode=73495
 *      File name =.~lock.setaALL.odt#	Inode=73490
 *      File name =setc1.c	Inode=73502
 *      File name =setaALL.pdf	Inode=73500
 *      File name =setb2.c	Inode=73499
 *      File name =setaALL.odt	Inode=73494
 *      File name =a.txt	Inode=73501
 *      File name =setb3.c	Inode=73493
 *      File name =setb1.c	Inode=73496
 *      File name =seta1.c	Inode=73498
 *      File name =a.out	Inode=73489
 *
 *      MYSHELL $]list F .
 *      seta2.c
 *      seta3.c
 *      .~lock.setaALL.odt#
 *      setc1.c
 *      setaALL.pdf
 *      setb2.c
 *      setaALL.odt
 *      a.txt
 *      setb3.c
 *      setb1.c
 *      seta1.c
 *      a.out
 *
 *      MYSHELL $]list N .
 *
 *      Total no. of entries in directory '.' = 14 
 *      MYSHELL $]^C
 *
 * [shalmali@localhost SHELL]$ 
 * */
