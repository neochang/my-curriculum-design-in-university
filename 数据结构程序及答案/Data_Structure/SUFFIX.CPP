#include <stdio.h>
#include <conio.h>

#define MAX 100

typedef struct Stack
{
	float c[MAX];
	int  top;
}MyStack;

//----------------------------------------
// Chang the input character into number.
//------------------------------------->>>
int Change(char c,int n)
{
	int k,a;
	k=(int)(c)-48;
	for(a=1;a<n;a++)
	{
		k*=10;
	}
	return(k);
} // end Change()

//------------------------------
// Initialize MyStack.
//--------------------------->>>
void InitStack(MyStack *s)
{
	s->top=-1;

} // end InitStack()

//------------------------------
// "Push" operation of MyStack.
//--------------------------->>>
void Push(MyStack &s,float x)
{
	int i;
	i=0;
	s.top++;
	s.c[s.top]=x;
	while(i<=s.top)
	{
	   printf("  %f",s.c[i]);
	   i++;
	}
	printf("\n");
} // end Push()

//------------------------------
// "Pop" operation of MyStack.
//--------------------------->>>
float Pop(MyStack &s)
{
	s.top--;
	return(s.c[s.top+1]);
} // end Pop()

//------------------------------
// Process the expression.
//--------------------------->>>
void DoStack(MyStack &s,char *m)
{
      //char a[5];
	int i,j,flag,n,sum;
	i=0;j=0;n=0;sum=0;
	float w;
	flag=0; // Judge if '-' is an operator or stand for Minus. 0 for operator, 1 for Minus.
	while(m[i]!='#')
	{ // While it is not the end of the expression.
		if(m[i]!=' '&&m[i]<='9'&&m[i]>='0')
		{ // The current character is a number.
			//a[j]=m[i];
			j++;
			//a[j]='%';
		  /*  First, process the character before Push.
		  If the current character is a number, record it with "j",
		  wait until meet a space. Then change all the characters
		  between the two spaces into an integer number.
		  As follows: */
		}
		else if(m[i]==' '&&m[i-1]>='0'&&m[i-1]<='9')
		{ // The current character is a space, and its previous character is a number.
			for(n=j;n>=1;n--)
			{
				sum+=Change(m[i-n],n);
			}
			if(flag==1)
				sum=-sum;
			Push(s,sum);
			flag=0;
			j=0;
			sum=0;
		}
		else if(m[i]=='+'||m[i]=='-'||m[i]=='*'||m[i]=='/')
		{ // The current character is an operator.
			switch(m[i])
			{
				case '+':
				{
					Push(s,Pop(s)+Pop(s));
					break;
				}
				case '-':
				{
					if(m[i+1]>='0'&&m[i+1]<='9')
					{
						flag=1; // '-' stand for Minus.
						break;
					}
					else
					{               // '-' stand for an operator.
						w=Pop(s);
						Push(s,Pop(s)-w);
						break;
					}
				}
				case '*':
				{
					Push(s,Pop(s)*Pop(s));
					break;
				}
				case '/':
				{
					w=Pop(s);
					if(w!=0)  Push(s,(float)Pop(s)/(float)w);
					break;
				}

			}
		}
	i++;
	} // end while(...)
} // end DoStack()

main()
{
	MyStack s;
	InitStack(&s);
	char n;
	char m[40];
	int i;
	i=0;
	printf(" \n  Please enter a SUFFIX expression( End with # ): \n  ");
	scanf("%c",&n);
	m[i]=n;
	while(n!='#')
	{
		scanf("%c",&n);
		i++;
		m[i]=n;
	}
	printf("  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("  The changes of stack are as follows:\n");
	printf("  -----------------------------------\n");
	DoStack(s,m);
	printf("  -----------------------------------\n");
	printf("\n  The result is : %f\n",s.c[s.top]);
	getch();
	return 0;
} // end main()
