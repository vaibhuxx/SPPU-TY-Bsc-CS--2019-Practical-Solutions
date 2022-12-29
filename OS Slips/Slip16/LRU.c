/*Write the simulation program for demand paging and show the page
scheduling and total number of page faults according the LRU page
replacement algorithm. Assume the memory of n frames.
Reference String
: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6
*/


//LRU
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node
{
	int pno;
	struct node *llink;
	struct node *rlink;
}NODE;

int noframes,noref,mat[10][20],frames[10];
NODE *first,*last;
NODE * getnode(int pno)
{
	NODE *t;
	t=(NODE *)malloc(sizeof(NODE));
	t->pno=pno;
	t->llink=NULL;
	t->rlink=NULL;
	return t;
}

void accept()
{
	int i,pno;
	NODE *p;
	printf("Enter No Of Frames: ");
	scanf("%d",&noframes);
	printf("Enter No Of References: ");
	scanf("%d",&noref);
	for(i=0;i<noref;i++)
	{
		printf("[%d]=",i);
		scanf("%d",&pno);
		p=getnode(pno);
		if(first==NULL)
			first=p;
		else
		{
			last->rlink=p;
			p->llink=last;
		}
	last=p;
	}
}
	
int search(int pno)
{
	int i;
	for(i=0;i<noframes;i++)
	if(frames[i]==pno)
	return i;
	return -1;
}

int get_lru(int e,NODE *p)
{
	int i,j,pos=999,posi;
	NODE *t;
	for(i=0;i<noframes;i++)
	{
		for(j=e-1,t=p->llink;j>=0;j--,t=t->llink)
		{
			if(frames[i]==t->pno)
			{
				if(pos>j)
				{
					pos=j;
					posi=i;
				}
			break;
			}
		}
	} 
	return posi;
}

void lru()
{
	int i,j,sp=0,faults=0;
	NODE *p;
	for(i=0,p=first;i<noref && sp<noframes;i++,p=p->rlink)
	{
		if(search(p->pno)==-1)
		{
			frames[sp]=p->pno;
			sp++;
			faults++;
			
			for(j=0;j<noframes;j++)
				mat[j][i]=frames[j];
		}
	}
		while(i<noref)
		{
			if(search(p->pno)==-1)
			{
				 sp=get_lru(i,p);
				 frames[sp]=p->pno;
				 faults++;
               			 for(j=0;j<noframes;j++)
        		         	mat[j][i]=frames[j];
               	        }
		
		i++;
		p=p->rlink;
	}


	for(p=first;p!=NULL;p=p->rlink)
	printf("%3d",p->pno);
	printf("\n\n");

	for(j=0;j<noframes;j++)
	{
		for(i=0;i<noref;i++)
		if (mat[j][i]!=0)
			printf("%3d",mat[j][i]);
		else
			printf("   ");
		printf("\n");
	}
	printf("Total No Of Page Faults are= %d",faults);
}

main() 
{
	accept();
	lru();
}
