/*Write the program to simulate preemptive Shortest Job First (SJF) –
scheduling. The arrival time and first CPU-burst of different jobs should be
input to the system. Accept no. of Processes, arrival time and burst time. The
output should give Gantt chart, turnaround time and waiting time for each
process. Also find the average waiting time and turnaround time
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10

typedef struct PROCESS
{
 char name[80] ;
 int at,bt,ct,wt,tat,tbt;
}PROCESS ;

PROCESS p[MAX] ;
int time,processCount;
float totaltat,totalwt,avgtat,avgwt ;

void sort()
{
 PROCESS p1 ;
 int i,j;
 for(i=0;i<processCount;i++)
    {
     for(j=i+1;j<processCount;j++)
		{
		 if(p[j].at < p[i].at)
			{
			 p1 = p[i] ;
			 p[i] = p[j] ;
			 p[j] = p1 ;
			}
		}
    }
}


void readProcess()
{
 int i ;
 printf("\nEnter the number of processes: ") ;
 scanf("%d",&processCount) ;
 for(i=0;i<processCount;i++)
    {
     printf("\nEnter the process name: ") ;
     scanf("%s",p[i].name) ;
     printf("Enter the CPU Burst time: ") ;
     scanf("%d",&p[i].bt) ;
     printf("Enter the Arrival time: ") ;
     scanf("%d",&p[i].at) ;
     p[i].tbt = p[i].bt ;
    }
 sort() ;
}

int getProcess()
{
 int i , min = 999 , p1 ;
 for(i=0;i<processCount;i++)
    {
     if(p[i].at <= time && p[i].tbt!=0)
       {
		if(p[i].tbt < min)
		  {
		   min = p[i].tbt ;
		   p1 = i ;
		  }
		}
    }
 return p1 ;
}


void scheduleProcess()
{
 int i,count=0 ;
 char currentprocess[10] , prevprocess[10] = "NULL" ;
 printf("\n\n  GanttChart:\n") ;
 printf("_________________________________________________\n") ;
 while(1)
      {
		i = getProcess() ;
		p[i].tbt-- ;
		strcpy(currentprocess,p[i].name) ;
		if(strcmp(currentprocess,prevprocess) !=0 )
		  {
		   printf("%d|%d  %s  ",time , time , currentprocess) ;
		  }
		time++ ;
		if(p[i].tbt==0)
		  {
		   p[i].ct = time ;
		   p[i].tat = time - p[i].at ;//finishtime-arrival time
		   p[i].wt = p[i].tat-p[i].bt ; //total existence-working time
		   count++ ;
		   totaltat += p[i].tat ;
		   totalwt+=p[i].wt ;
		  }
		strcpy(prevprocess , currentprocess) ;
		if(count==processCount)
		  break ;
		  }
 printf("%d|",time) ;
 printf("\n_________________________________________________\n") ;
 avgtat =totaltat/processCount ;
 avgwt = totalwt/processCount ;
}

void display()
{
 int i;
 printf("\n--------------------------------------------------------------------------------\n") ;
 printf("Process  ArrivalTime  BurstTime  CPUTime  TurnAroundtime  WaitTime\n");
 printf("--------------------------------------------------------------------------------\n");
 for(i=0 ; i<processCount ; i++)
    printf("%s\t  %d\t\t%d\t  %d\t   %d\t\t   %d\n",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt) ;
 printf("--------------------------------------------------------------------------------") ;
 printf("\n\nTotal Turn Around Time: %f",totaltat) ;
 printf("\nTotal Wait Time: %f",totalwt) ;
 printf("\n\nAverage Turn Around Time: %f",avgtat) ;
 printf("\nAverage Wait Time: %f\n",avgwt) ;
}

int main()
{
 //clrscr();
 readProcess();
 scheduleProcess();
 display();
 //getch();
 return 0;
}