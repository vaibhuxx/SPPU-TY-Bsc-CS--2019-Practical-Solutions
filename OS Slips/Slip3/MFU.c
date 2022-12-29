//Write the simulation program for demand paging and show the page
 //scheduling and total number of page faults according the MFU page
 //replacement algorithm. Assume the memory of n frames.
//Reference String : 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int pno;
  struct node *link;
} NODE;
int noframes, noref, mat[10][20], frames[10], count[10];
NODE *first, *last;
NODE *getnode(int pno)
{
  NODE *t;
  t = (NODE *)malloc(sizeof(NODE));
  t->pno = pno;
  t->link = NULL;
  return t;
}
void accept()
{
  int i, pno;
  NODE *p;
  printf("Enter the no of frames");
  scanf("%d", &noframes);
  printf("Enter the no of references");
  scanf("%d", &noref);
  for (i = 0; i < noref; i++)
  {
    printf("[%d]=", i);
    scanf("%d", &pno);
    p = getnode(pno);
    if (first == NULL)
      first = p;
    else
      last->link = p;
    last = p;
  }
}
int search(int pno)
{
  int i;
  for (i = 0; i < noframes; i++)
    if (frames[i] == pno)
      return i;
  return -1;
}
int get_mfu(int s)
{
  int cnt = -999, posi, i;
  i = s;
  do
  {
    if (count[i] > cnt)
    {
      cnt = count[i];
      posi = i;
    }
    i = (i + 1) % noframes;
  }
  while (i != s);
    return posi;
}
void mfu()
{
  int sp = 0, faults = 0, i, j, k;
  NODE *p;
  for (i = 0, p = first; sp < noframes; i++, p = p->link)
  {
    k = search(p->pno);
    if (k == -1)
    {
      frames[sp] = p->pno;
      count[sp] = 1;
      sp++;
      faults++;
      for (j = 0; j < noframes; j++)
        mat[j][i] = frames[j];
    }
    else
      count[k]++;
  }
  sp = 0;
  while (i < noref)
  {
    k = search(p->pno);
    if (k == -1)
    {
      sp = get_mfu(sp);
      frames[sp] = p->pno;
      count[sp] = 1;
      faults++;
      sp = (sp + 1) % noframes;
      for (j = 0; j < noframes; j++)
        mat[j][i] = frames[j];
    }
    else
      count[k]++;
    i++;
    p = p->link;
  }
  for (p = first; p != NULL; p = p->link)
    printf("%3d", p->pno);
  printf("\n\n");
  for (j = 0; j < noframes; j++)
  {
    for (i = 0; i < noref; i++)
      if (mat[j][i] != 0)
        printf("%3d", mat[j][i]);
      else
       printf(" ");
       printf("\n");
  }
  printf("\n Total no of page faults=%d", faults);
}
main()
{
  accept();
  mfu();
}