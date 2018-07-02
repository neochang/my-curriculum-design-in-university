//////////////////////////////////////////////////////
//  Test this program with the following data:      //
//   ABC##DE#G##F###(PreOrder)                      //
//////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

typedef struct btnode{
   char data;
   struct btnode *first_child,*next_sibling;
   } btnode,*bitretp;

bitretp bt;

void  crt_tree(bitretp &bt)
{
  char ch;
  scanf("%c",&ch);
  if (ch=='#') bt=NULL;
  else{ 
            bt=(bitretp)malloc(sizeof(btnode));
	    bt->data=ch;
	    crt_tree(bt->first_child);
	    crt_tree(bt->next_sibling);
       }
}

void preorder(bitretp bt)
{
  if(bt)
    {
     printf("%c",bt->data);
     preorder(bt->first_child);
     preorder(bt->next_sibling);
    }
}  // preorder

int LeafCount_CSTree(bitretp T)
{
 int count;
 bitretp child;
 if (!T) return 0;
 else if(!T->first_child)
  {
   printf("%c ",T->data);
   return 1;
  }
 else
  {
   count=0;
   for(child=T->first_child;child;child=child->next_sibling)
      count+=LeafCount_CSTree(child);
    return count;
  }
} // end LeafCount_CSTree()

int GetDepth_CSTree(bitretp T)
{
  int maxd,d;
  bitretp p;
  if(!T) return 0;
  else
  {
    for(maxd=0,p=T->first_child;p;p=p->next_sibling)
      if((d=GetDepth_CSTree(p))>maxd) maxd=d;
    return maxd+1;
  }
}//GetDepth_CSTree 


void main()
{
 bitretp bt;
 int LeafCount,Depth;
 printf("  Create a Tree, input by PreOrder:\n  ");
 crt_tree(bt);
 
 printf("  Output by PreOrder:\n  ");
 preorder(bt);
 printf("\n\n");
 
 printf("  The Leaf Nodes are:\n  ");
 LeafCount=LeafCount_CSTree(bt);
 printf("\n\n"); 
 printf("  The number of leaves is: %d\n  ",LeafCount);
 printf("\n");

 Depth=GetDepth_CSTree(bt);
 printf("  The depth of the tree is: %d\n  ",Depth);
 printf("\n");
 getch();
}