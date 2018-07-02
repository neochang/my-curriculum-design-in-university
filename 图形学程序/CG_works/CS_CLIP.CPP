/////////////////***************************////////////////////////
// This program includes the implementation of the algorithm of
// Cohen-Sutherland (C-S) Line Clip.
////////////////***************************////////////////////////

#include<graphics.h>
#include<conio.h>
#include<stdio.h>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

//#define DeBug

 #ifdef DeBug
 float x_1,y_1,x_2,y_2;
 #endif

int encode(float x,float y,float xl,float xr,float yb,float yt)
{
  int c=0;
  if(x<xl) c|=LEFT;
  if(x>xr) c|=RIGHT;
  if(y<yb) c|=BOTTOM;
  if(y>yt) c|=TOP;
  return (c);
}

void CS_Clip(float x1,float y1,float x2,float y2,float XL,float XR,float YB,float YT)
{
  int code1,code2,code;
  float x,y;
  float internal_XL,internal_XR,internal_YB,internal_YT;

  internal_XL=XL;
  internal_XR=XR;
  internal_YB=YB;
  internal_YT=YT;

  code1=encode(x1,y1,internal_XL,internal_XR,internal_YB,internal_YT);
  #ifdef DeBug
  printf("\n  code1:%d",code1);
  #endif
  code2=encode(x2,y2,internal_XL,internal_XR,internal_YB,internal_YT);
  #ifdef DeBug
  printf("\n  code2:%d\n",code2);
  #endif

  while(code1!=0||code2!=0)
  {
    if((code1&code2)!=0)
	return;
    // return: Exits immediately from the currently executing function to the calling routine.
    code=code1;
    if(code==0)
       {
	code=code2;
	#ifdef DeBug
	printf("\n  code:%d\n",code);
	#endif
       }
    if((LEFT&code)!=0)
    {
      x=XL;
      #ifdef DeBug
      printf("  x:%f",x);
      #endif
      y=y1+(y2-y1)*(XL-x1)/(x2-x1);
      #ifdef DeBug
      printf("  y:%f\n",y);
      #endif
    }
    else if((RIGHT&code)!=0)
    {
      x=XR;
      #ifdef DeBug
      printf("  x:%f",x);
      #endif
      y=y1+(y2-y1)*(XR-x1)/(x2-x1);
      #ifdef DeBug
      printf("  y:%f\n",y);
      #endif
    }
    else if((BOTTOM&code)!=0)
    {
      y=YB;
      #ifdef DeBug
      printf("  y:%f",y);
      #endif
      x=x1+(x2-x1)*(YB-y1)/(y2-y1);
      #ifdef DeBug
      printf("  x:%f\n",x);
      #endif
    }
    else if((TOP&code)!=0)
    {
      y=YT;
      #ifdef DeBug
      printf("  y:%f",y);
      #endif
      x=x1+(x2-x1)*(YT-y1)/(y2-y1);
      #ifdef DeBug
      printf("  x:%f\n",x);
      #endif
    }
    if(code==code1)
    {
      x1=x;y1=y;
      #ifdef DeBug
      printf("\n  x1:%f y1:%f",x1,y1);
      #endif
      code1=encode(x,y,internal_XL,internal_XR,internal_YB,internal_YT);
      #ifdef DeBug
      printf("\n  code1:%d",code1);
      #endif
    }
    else
    {
      x2=x;y2=y;
      #ifdef DeBug
      printf("\n  x2:%f y2:%f",x2,y2);
      #endif
      code2=encode(x,y,internal_XL,internal_XR,internal_YB,internal_YT);
      #ifdef DeBug
      printf("\n  code2:%d",code2);
      #endif
    }
  }
  line(x1,y1,x2,y2);
  #ifdef DeBug
  x_1=x1;y_1=y1;x_2=x2;y_2=y2;
  #endif
}

void main()
{
  int graphdrive=DETECT,graphmode;
  float x1,y1,x2,y2;
  float XL,XR,YB,YT;

  printf("\n  Please input the starting point and the end point of the line:");
  printf("\n  X1:");
  scanf("%f",&x1);
  printf("\n  Y1:");
  scanf("%f",&y1);
  printf("\n  X2:");
  scanf("%f",&x2);
  printf("\n  Y2:");
  scanf("%f",&y2);
  printf("\n  Please enter the edge of the Clip Window:");
  printf("\n  LEFT:");
  scanf("%f",&XL);
  printf("\n  RIGHT:");
  scanf("%f",&XR);
  printf("\n  TOP:");
  scanf("%f",&YT);
  printf("\n  BOTTOM:");
  scanf("%f",&YB);
  printf("\n  All data collected, Press any key to continue...");
  getch();

  initgraph(&graphdrive,&graphmode,"");
  cleardevice();
  setcolor(9);
  line(x1,y1,x2,y2); // Draw the original line.
  getch();
  setcolor(10);
  line(XL,YT,XL,YB); // Draw the Clip Window.
  line(XL,YT,XR,YT); //---|  |  |
  line(XR,YT,XR,YB); //------|  |
  line(XL,YB,XR,YB); //---------|
  getch();
  setcolor(14);
  CS_Clip(x1,y1,x2,y2,XL,XR,YB,YT); // Clip the original line.
  getch();
  closegraph();
  #ifdef DeBug
  printf("\n X1':%f Y1':%f X2':%f Y2':%f",x_1,y_1,x_2,y_2);
  getch();
  #endif
}  // end main()