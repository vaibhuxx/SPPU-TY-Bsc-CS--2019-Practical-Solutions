/*Write the simulation program for Round Robin scheduling for given time
 quantum. The arrival time and first CPU-burst of different jobs should be input
 to the system. Accept no. of Processes, arrival time and burst time. The output
 should give the Gantt chart, turnaround time and waiting time for each
 process. Also display the average turnaround time and average waiting time. 
*/


//RR
#include<stdio.h>
#include<string.h>

struct input
{
char jname[10];
int at,bt,tbt,ct;
}tab[5],t;

struct s
{
char jname[10];
int end,start;
}seq[20],seq1[20];

int j,k,n,time=0,finish=0,prev=0;

input()
{
int i;
	printf("enter the no of jobs :");
	scanf("%d",&n);
	printf("Job\tBT\tAT\n");
	for(i=0;i<n;i++)
	{
		scanf("%s%d%d",&tab[i].jname,&tab[i].bt,&tab[i].at);
		tab[i].tbt=tab[i].bt;
	}
}

sort()
{
int i;
for(i=0;i<n;i++)
{
	for(j=i+1;j<n;j++)
	{
		if(tab[i].at>tab[j].at)
		{
			t=tab[i];
			tab[i]=tab[j];
			tab[j]=t;
		}
	}
}
}

print_input()
{
int i;
printf("\nJOB\tBT\tAT\n");
for(i=0;i<n;i++)
	printf("%s\t%d\t%d\n",tab[i].jname,tab[i].bt,tab[i].at);
}

int arrived(int i)
{
	if(tab[i].tbt!=0 && tab[i].at<=time)
	 	return 1;
	else
		return 0;
}

process()
{
int i=0;
k=0;
while(finish<n)
{
	if(arrived(i))
	{
		if(tab[i].tbt<=2)
		{
			finish++;
			seq[k].start=prev;
			time+=tab[i].tbt;
			tab[i].ct=time;
			seq[k].end=time;
			strcpy(seq[k++].jname,tab[i].jname);
			tab[i].tbt=0;
			prev=time;
		}
		else
		{
			tab[i].tbt-=2;		
			seq[k].start=prev;
			time+=2;
			tab[i].ct=time;
			seq[k].end=time;
			strcpy(seq[k++].jname,tab[i].jname);
			prev=time;						
		}
	}
	i++;
	if(i==n)
	{i=0;}
}
}

gant_chart()
{
int i=0;
printf("\nGant chart:\n");
for(i=0;i<k;i++)
	printf("|  %d_%s_%d  ",seq[i].start,seq[i].jname,seq[i].end);
}

print_output()
{
int i,t1,t2;
float tat=0,twt=0;
printf("\nJob\tTAT\tWT");
for(i=0;i<n;i++)
{
	t1=tab[i].ct-tab[i].at;
	t2=tab[i].ct-tab[i].at-tab[i].bt;
	printf("\n%s\t%d\t%d",tab[i].jname,t1,t2);
	tat+=t1;twt+=t2;
}
printf("\nAvgTAT =%f\nAvgWT=%f",tat/n,twt/n);
}

main()
{
input();
sort();
print_input();
process();
print_output();
gant_chart();
}