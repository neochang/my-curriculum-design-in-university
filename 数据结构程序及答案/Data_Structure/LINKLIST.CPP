#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LEN sizeof(LNode)

typedef struct LNode{
  int data;
  struct LNode *next;
}LNode,*LinkList;

LinkList ListCreat();
LinkList ListInsert(LinkList &);
void ListPrint(LinkList &);
LinkList ListDelete(LinkList &);
void ListFind(LinkList &);
void ListGet(LinkList &);

LinkList ListCreat()
{
     int n;
     LinkList L;
     L=(LinkList)malloc(LEN);
     L->next=NULL;
    // printf("\n Input numbers of nodes you want to creat:\n ");
    // scanf("%d",&n);
     for(int i=20/* n */;i>0;--i)
     {
       LinkList p;
       p=(LinkList)malloc(LEN);
      // printf("\n Input integer numbers for the data area:\n");
      // scanf("%d",&p->data);
       p->data=abs(rand()%10);
       p->next=L->next;L->next=p;
     }
     return(L);
}

LinkList  ListInsert(LinkList &L)
{
    int e,i;
    printf("\n Input the integer data you want to insert:\n");
    scanf("%d",&e);
pos:printf("\n Input the position you want to insert in(before which data):\n");
    scanf("%d",&i);
    LinkList p=L;
    LinkList s;
    int j=0;
    while(p&&j<i-1)
    {
      p=p->next;++j;
    }
    if(!p||j>i-1)
    {
      printf("\n The insert position you've given are not appropriate!\n");
      goto pos;
    }
    s=(LinkList)malloc(LEN);
    s->data=e;
    s->next=p->next;
    p->next=s;
    printf("\n The data has been inserted in the list!The new list are:");
    ListPrint(L);
    return(L);
}

LinkList ListDelete(LinkList &L)
{
    int i,e;
pos2:printf("\n Input the position of the data you want to delete:\n");
    scanf("%d",&i);
    LinkList p=L;
    LinkList q;
    int j=0;
    while(p->next&&j<i-1)
    {
      p=p->next;++j;
    }
    if(!(p->next)||j>i-1)
    {
      printf("\n The position you've input is not appropriate:\n");
      goto pos2;
    }
    q=p->next; // p->next is the one to delete.
    p->next=q->next;
    e=q->data;
    free(q);
    printf("\n Successfully Delete!The deleted data is %d\n",e);
    ListPrint(L);
    return(L);
}

void ListPrint(LinkList &L)
{
     LNode *p;
     p=L->next;
     printf("\n These nodes are as follows:\n");
     if(p!=NULL)
     do
     {
       printf("%d   ",p->data);
       p=p->next;
     }while(p!=NULL);
}
void ListFind(LinkList &L)
{
  int i=1;
  int x;
  LinkList p;
  p=L->next;
  printf("\n Input the data you want to find:\n");
  scanf("%d",&x);
  while(p&&p->data!=x)
  {
    p=p->next;
    i++;
  }
  if(p)
    printf("\n Find the data successfully!The position is %d",i);
  else
    printf("\n There isn't such a data in the list.\n");
}
void ListGet(LinkList &L)
{
  LinkList p;
  int i,j,e;
  j=0;
  p=L;
pos3:printf("\n Input the position of data you want to get:\n");
  scanf("%d",&i);
  while(p&&j<i)
  {
    p=p->next;
    j++;
  }
  if(p->next!=NULL)
    {
      e=p->data;
      printf("\n The %dth data is %d:\n",i,e);
    }
    else
    {
      printf("\n The position you've input is not appropriate:\n");
      goto pos3;
    }
}

void main()
{
  int n;	
  LinkList L;
  L=(LinkList)malloc(LEN);

  printf("\n First,Create a LinkList:");
  L=ListCreat();
  ListPrint(L);
rs:printf("\n Please select the operation you want:\n");
  printf("\n 1.Insert a number to the LinkList");
  printf("\n 2.Delete a number from the LinkList");
  printf("\n 3.Find a number in the LinkList");
  printf("\n 4.Get a number of a paticular position");
  printf("\n 5.Print the LinkList");
  printf("\n 6.Exit\n");
  printf("\n Your selection:");
  scanf("%d",&n);

  switch(n)
  {
   case 1 : { ListInsert(L);goto rs;}
   case 2 : { ListDelete(L);goto rs;}
   case 3 : { ListFind(L);goto rs;}
   case 4 : { ListGet(L);goto rs;}
   case 5 : { ListPrint(L);goto rs;}
   case 6 : exit(0);
   default: {
   	     printf("Invalid input!!");
   	     goto rs;
   	    }
  }
}