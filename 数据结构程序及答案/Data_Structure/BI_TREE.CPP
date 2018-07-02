//////////////////////////////////////////////////////
//  Test this program with the following data:      //
//   ABC##DE#G##F###(PreOrder)                      //
//////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>
#include <conio.h>

typedef struct btnode{
   char data;
   struct btnode *lchild,*rchild;
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
	    crt_tree(bt->lchild);
	    crt_tree(bt->rchild);
       }
}

void preorder(bitretp bt)
{
  if(bt)
    {
     printf("%c",bt->data);
     preorder(bt->lchild);
     preorder(bt->rchild);
    }
}  // preorder

void  inorder(bitretp bt)
{
  if (bt)
   {
    inorder(bt->lchild);
    printf("%c",bt->data);
    inorder(bt->rchild);
    }
} // inorder

void  postorder(bitretp bt)
{
  if(bt)
    {
     postorder(bt->lchild);
     postorder(bt->rchild);
     printf("%c",bt->data);
    }
} // postorder

int LeafCount_BiTree(bitretp T)
{
 if (!T) return 0;
 else if(!T->lchild&&!T->rchild)
  {
   printf("%c ",T->data);
   return 1;
  }
 else
   return(LeafCount_BiTree(T->lchild)+LeafCount_BiTree(T->rchild));
} // end LeafCount_BiTree()

int Get_Depth(bitretp T)
{
  int m,n;
  if(!T) return 0;
  else
  {
    m=Get_Depth(T->lchild);
    n=Get_Depth(T->rchild);
    return (m>n?m:n)+1;
  }
} // end Get_Depth()

void BiTree_eXchange(bitretp T)
{
  bitretp temp_T;
  temp_T=T->lchild;
  T->lchild=T->rchild;
  T->rchild=temp_T;
  if(T->lchild)
    BiTree_eXchange(T->lchild);
  if(T->rchild)
    BiTree_eXchange(T->rchild);
} // end BiTree_eXchange()

void main()
{
 bitretp bt;
 int LeafCount,Depth;
 printf("  Create a Tree, input by PreOrder:\n  ");
 crt_tree(bt);
 
 printf("  Output by PreOrder:\n  ");
 preorder(bt);
 printf("\n\n");
 
 printf("  Output by InOrder:\n  ");
 inorder(bt);
 printf("\n\n");
 
 printf("  Output by PostOrder:\n  ");
 postorder(bt);
 printf("\n\n");
 
 printf("  The Leaf Nodes are:\n  ");
 LeafCount=LeafCount_BiTree(bt);
 printf("\n\n"); 
 printf("  The number of leaves is: %d\n  ",LeafCount);
 printf("\n");
 
 Depth=Get_Depth(bt);
 printf("  The depth of the tree is: %d\n  ",Depth);
 printf("\n");
 
 printf("  Now,exchange all the SubTrees...\n  And the result is(PreOrder):\n  ");
 BiTree_eXchange(bt);
 preorder(bt);
 getch();
}