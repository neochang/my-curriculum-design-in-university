#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

/*typedef struct{
   int *base;
   int *top;
   int stacksize;
}SqStack; */

typedef struct{
   char *base;
   char *top;
   int  stacksize;
}SqStack;

int InitStack(SqStack &S)
{
 S.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
 if(!S.base)
 {
   printf("\n  Allocate store space failed!!");
   getch();
   exit(0); // Allocation failure.
 }
 S.top=S.base;
 S.stacksize = STACK_INIT_SIZE;
 return(1);
}

int Push( SqStack &S, char e )
{
 if( S.top - S.base >= S.stacksize) // Stack is full.
 {
  S.base = (char *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
  if (!S.base)
  {
      printf("\n  Reallocate store space failed!!");
      getch();
      exit(0);
  }
  S.top = S.base + S.stacksize;
  S.stacksize += STACKINCREMENT;
 }
 *S.top++ = e;
 return(1);
}

char Pop(SqStack &S)
{
 char e;
 if (S.top == S.base) // Stack is empty.
    return(0);
 e = * --S.top;
 return(e);
}

void main()
{
 FILE *fp;
 char ch,ch_pop,filename[50];
 SqStack S;
 int count=0;
 
 InitStack(S);
 printf("\n  Please input the name of the file you want to check:\n  ");
 scanf("%s",filename);
 if ((fp=fopen(filename,"r"))==NULL)
 {
   printf("\n  Cannot open file!!\n");
   getch;
   exit(0);
 }
 while(!feof(fp))
 {
   ch=fgetc(fp);
   if ( (ch=='(')||(ch=='[')||(ch=='{') )
      Push(S,ch);
   else if ( (ch==')')||(ch==']')||(ch=='}') )
   {
      if(S.top==S.base) // Stack is empty.
      {
      	//printf("\n  %d error(s) found.\n",count);
      	count++;
      	continue;
      }
      ch_pop=Pop(S);
      if( (ch==')')&&(ch_pop!='(') )
      {
      	//printf("\n  %d error(s) found.\n",count);
      	count++;
      }
      if( (ch==']')&&(ch_pop!='[') )
      {
      	//printf("\n  %d error(s) found.\n",count);
      	count++;
      }
      if( (ch=='}')&&(ch_pop!='{') )
      {
      	//printf("\n  %d error(s) found.\n",count);
      	count++;
      }
   } // end "else if..."
 } // end while()
 
 if(S.top!=S.base)
 {
   while(S.top!=S.base)
   {
     Pop(S);
     //printf("\n  %d error(s) found.\n",count);
     count++;
   }
 }
 printf("\n  %d error(s) found.\n",count);
 fclose(fp);
} //end main()