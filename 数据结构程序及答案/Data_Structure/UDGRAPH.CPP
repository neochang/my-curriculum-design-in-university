////////////////////////////////////////////////////
// This program includes the implementation of:   //
// (1) Adjacency List for UndiGraph               //
// (2) Breadth First Search of the UndeGraph      //
////////////////////////////////////////////////////

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAXQSIZE 100
#define OK       1
#define ERROR    0

/////////////////////////////////////
///-- Data type define for Graph -->>
typedef struct arcnode{
     int adjvex;
     struct arcnode *nextarc;
} *arcptr,arc_node;

typedef struct {
	char verdata[10];
	arcptr firstarc;
} vernode;

typedef struct {
	vernode adjlist[30];
	int n;  // the number of vertexes.
	int e;  // the number of edges
} adjgraph;
///-- Data type define for Graph --<<

////////////////////////////////////
//-- Data type define for Queue -->>
typedef struct {
	int *base;
	int front;
	int rear;
} SqQueue;
//-- Data type define for Queue --<<

///////////////////////////////////
//---- The Operation of Queue --->>
int InitQueue(SqQueue &Q)
{
  Q.base=(int *)malloc(MAXQSIZE*sizeof(int));
  if(!Q.base) exit(0);
  Q.front=0;
  Q.rear=0;
  return OK;
} // end InitQueue()

int AddQueue(SqQueue &Q,int e)
{
  if((Q.rear+1)%MAXQSIZE==Q.front)
      return ERROR;  // Queue is full.
  Q.base[Q.rear]=e;
  Q.rear=(Q.rear+1)%MAXQSIZE;
  return OK;
} // end AddQueue()

int DelQueue(SqQueue &Q,int &e)
{
  if(Q.front==Q.rear)
     return ERROR;  // Queue is empty.
  e=Q.base[Q.front];
  Q.front=(Q.front+1)%MAXQSIZE;
  return OK;
} // end DelQueue()

int Qempty(SqQueue &Q)
{
  if(Q.front==Q.rear)
   return 1;
  else
   return 0;
} // end Qempty()
//---- The Operation of Queue ---<<

////////////////////////////////////////////
//--- Build Adjacency List for Graph ---->>>
void build_adjlist(adjgraph &graph)
{
  int vernum,edgenum,i,k,head,tail;
  arcptr p;

  printf("  Please input the number of Vertexes(<=30):\n  ");
  scanf("%d",&vernum);
  if ((vernum<0)||(vernum>30))
  {
    printf("  ERROR!! The number of vertexes cannot be negative or over 30!\n  ");
    getch();
    exit(0);
  }
  printf("  Please input the number of Edges:\n  ");
  scanf("%d",&edgenum);
  if ((edgenum<0)||(edgenum>(vernum*(vernum-1))/2))
  {
    printf("  ERROR!! The number of edges cannot be negative or over VerNum*(VerNum-1)/2 !\n  ");
    getch();
    exit(0);
  }

  graph.n=vernum;
  graph.e=edgenum;

  printf("  Please input data for the nodes:\n");
  for(i=0;i<graph.n;i++)
  {
    printf("  VERTEX[%d]:",i+1);
    scanf("%c"); // read the CR-LF;
    scanf("%s",&graph.adjlist[i].verdata);
    //graph.adjlist[i].verdata=getchar();
    graph.adjlist[i].firstarc=NULL;
    printf("\n");
  }

  printf("  Now,Create edges...\n");
  printf("  Input the two vertexes for each edge:\n");
  for(k=0;k<graph.e;k++)
  {
    printf("  EDGE[%d]:\n",k+1);
    printf("           Node1:");
    scanf("%d",&head);
    printf("           Node2:");
    scanf("%d",&tail);

    //The node which reads first comes to the end of the linklist.
    p=(arcptr)malloc(sizeof(arc_node));
    p->adjvex=tail-1;
    p->nextarc=graph.adjlist[head-1].firstarc;
    graph.adjlist[head-1].firstarc=p;

    //the graph is a Undigraph,so...
    p=(arcptr)malloc(sizeof(arc_node));
    p->adjvex=head-1;
    p->nextarc=graph.adjlist[tail-1].firstarc;
    graph.adjlist[tail-1].firstarc=p;
  }
} // end build_adjlist()
//--- Build Adjacency List for Graph ----<<<

/////////////////////////////////////
//--- Breadth First Search ------->>>
void BFS(adjgraph g,int v)
{
  int visited[30];
  int w,i;
  SqQueue Q;
  arcptr ptr;

  for(i=0;i<30;i++)
     visited[i]=0;
  InitQueue(Q);
  printf("  V%d: %s\n",v,g.adjlist[v-1].verdata);
  visited[v]=1;
  AddQueue(Q,v);
  while(!Qempty(Q))
  {
    DelQueue(Q,v);
    ptr=g.adjlist[v-1].firstarc;
    while(ptr!=NULL)
    {
      w=ptr->adjvex;
      if(visited[w+1]==0)
      {
	printf("  V%d: %s\n",w+1,g.adjlist[w].verdata);
	visited[w+1]=1;
	AddQueue(Q,w+1);
      }
      ptr=ptr->nextarc;
    } // end while(ptr!=NULL)
  } // end while(!Qempty(Q))
} // end BFS()
//--- Breadth First Search -------<<<


void main()
{
 adjgraph UDG;
 arcptr q;
 int m,start_ver;

 printf("  Create the Adjacency List....\n  -----------------------------\n");
 build_adjlist(UDG);
 printf("\n  Created successfully! Press any key to view the result...\n\n");
 getch();
 printf("  The Adjacency List is:\n  ----------------------------\n");
 for(m=0;m<UDG.n;m++)
 {
   printf("  V%d:%s  ",m+1,UDG.adjlist[m].verdata);
   q=UDG.adjlist[m].firstarc;
   while(q!=NULL)
   {
     printf("->");
     printf(" V%d ",(q->adjvex)+1);
     q=q->nextarc;
   }
   printf("-> NULL\n");
 }
 printf("  ----------------------------\n");
 getch();
 getch();
 ///////////////////////////////////////////////////////////
 printf("\n  Now, Search the graph by Breadth First Order...");
 getch();
 getch();
 printf("\n  Please input the number of start vertex:\n  ");
 scanf("%d",&start_ver);
 if((start_ver<=0)||(start_ver>UDG.n))
 {
   printf("  ERROR!! Wrong Vertex Number!");
   getch();
   exit(0);
 }
 printf("  Press any key to continue...\n");
 getch();
 BFS(UDG,start_ver);
 printf("\n\n  BFS OK!\n");
 getch();
 getch();
}