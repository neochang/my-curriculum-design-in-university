/////////////////***************************////////////////////////
// This program includes the implementation of the algorithm of
// Non_Recursive_Seed_Fill.
////////////////***************************////////////////////////

#define LEFT 0
#define RIGHT 639
#define TOP 0
#define BOTTOM 479
#include <stdio.h>
#include <conio.h>
#include <graphics.h>


int TAB_TERM[600];
int PUSH_POINT=0;
int POP_POINT=0;

void scan_board(int seed_x,int seed_y,int *x_left,int *x_right,int f_color,int g_color)
{
  int x,y;
  x=seed_x; y=seed_y;
  while(1)
   {
     --x;  // Search the left boundary
     if(x<=LEFT) break;
     if(getpixel(x,y)!=g_color) break;
   }
   *x_left=++x;
   while(1)
   {
     ++x;  // Search the right boundary
     if(x>=RIGHT) break;
     if(getpixel(x,y)!=g_color) break;
   }
   *x_right=--x;
   setcolor(f_color);
   line(*x_left,y,*x_right,y);
   getch();
}

//***** PUSH the boundary pixel *****//
void push_x(int x_left,int x_right,int seed_y)
{
  if(PUSH_POINT>=600) PUSH_POINT=0;
  TAB_TERM[PUSH_POINT]=x_left;
  PUSH_POINT++;
  TAB_TERM[PUSH_POINT]=x_right;
  PUSH_POINT++;
  TAB_TERM[PUSH_POINT]=seed_y;
  PUSH_POINT++;
} 

//***** POP the boundary pixel *****//
void pop_x(int *x_left,int *x_right,int *seed_y)
{
  if(POP_POINT>=600) POP_POINT=0;
  *x_left=TAB_TERM[POP_POINT];
  POP_POINT++;
  *x_right=TAB_TERM[POP_POINT];
  POP_POINT++;
  *seed_y=TAB_TERM[POP_POINT];
  POP_POINT++;
}

//***** Fill the fixed area *****//
void fill_area(int x,int y,int f_color)
{
  int color,g_color;
  int x1,xr,y_up,y_down,i,x_left,x_right;
  PUSH_POINT=0; POP_POINT=0;
  /* Judge if the point (x,y) is the seed */
  if (x<0 || x>=RIGHT) return;
  if (y<0 || y>=BOTTOM) return;
  g_color=getpixel(x,y);
  if(f_color==g_color) return;
  /* When the point (x,y) is the seed */
  scan_board(x,y,&x1,&xr,f_color,g_color);
  push_x(x1,xr,y);
  
  while(PUSH_POINT!=POP_POINT)
  {
    pop_x(&x1,&xr,&y);
    y_up=y;
    y_down=y;
    if(y_up>TOP)
      y_up--;     // go upwards
    if(y_down<BOTTOM)
      y_down++;   // go downwards
    /* Seek seed on the Previous scanning-line and Next scanning-line */
    for(i=x1;i<xr;i++)
    {
      color=getpixel(i,y_up);//Seek seed on the Previous scanning-line
      if(color==g_color)
      {
       scan_board(i,y_up,&x_left,&x_right,f_color,g_color);
       push_x(x_left,x_right,y_up);
      }
      color=getpixel(i,y_down);//Seek seed on the Next scanning-line  
      if(color==g_color)
      {
       scan_board(i,y_down,&x_left,&x_right,f_color,g_color);
       push_x(x_left,x_right,y_down);
      }
    }
  }  // end while()
}  // end fill_area()

/*void main()  // This is the original main() function.
{
  int x,y,f_color;
  int d[]={160,50,115,75,115,125,160,150,205,125,205,75,160,50};
  int graphdrive=DETECT,graphmode;
  initgraph(&graphdrive,&graphmode,"");
  cleardevice(); setcolor(8);
  drawpoly(7,d); // Draw Polygon
  x=130;y=100; // Coordinates of the seed
  f_color=3;
  fill_area(x,y,f_color);
  getch();
  closegraph();
}*/
////******** The Modified main() Function *******>>>>
void main()
{
  int x,y,f_color,test_color,temp_y1,temp_y2;
  int pPolygonVertexes[40];
  int i,j,n;
  int graphdrive=DETECT,graphmode;
  i=0;
  j=0;
  printf("\n  Please input the number of the Polygon's Vertexes:");
  printf("\n  N<=20:");
  scanf("%d",&n);
  printf("\n  Pleasw input the coordinates of the Polygon's Vertexes:\n");
  //////////*************************
  do
  {
    printf("\n  X[%d]:",j+1);
    scanf("%d",&pPolygonVertexes[i]);
    i++;
    printf("\n  Y[%d]:",j+1);
    scanf("%d",&pPolygonVertexes[i]);
    i++;
    j++;
  }while(j<n);

  pPolygonVertexes[i]=pPolygonVertexes[0];
  i++;
  pPolygonVertexes[i]=pPolygonVertexes[1];
  ////******************************
  printf("\n  All data collected, Press any key to continue...");
  getch();

  initgraph(&graphdrive,&graphmode,"");
  cleardevice(); setcolor(10);
  drawpoly(n+1,pPolygonVertexes); // Draw Polygon
  //********************************************************>>>>
  // The algorithm of Seek the Seed.
  // Create Date:  2003-10-7
  // By:  Zhang Wei
  /////////////---------------------->>>>
  x=0;y=0;
  //*** Seek from left to right, 0 to BOTTOM, horizontally. ***
  for(y=0;y<=BOTTOM;y++)
  {
    for(x=0;x<=RIGHT;x++)
    {
      test_color=getpixel(x,y);
      if(test_color==10)
      {
	  temp_y1=y;
	  goto reverse_seek;
      }
    }
  }
  //*** Seek from left to right, BOTTOM to 0, horizontally. ***
  reverse_seek: for(y=BOTTOM;y>=0;y--)
   {
     for(x=0;x<=RIGHT;x++)
     {
      test_color=getpixel(x,y);
      if(test_color==10)
      {
	temp_y2=y;
	goto Mid_point;
      }
     }
   }
  Mid_point: y=(temp_y1+temp_y2)/2;
  //*** Seek from left to right, at the horizontal line of Middle_point. ***
             for(x=0;x<=RIGHT;x++)
             {
             	test_color=getpixel(x,y);
             	if(test_color==10)
             	    break;
             }
  /* Seed Found: */ 
                    x=x+1;       
  //////**** The seed is (x,y) <<<<**** End the Algorithm **********///
  f_color=14;
  fill_area(x,y,f_color);
  getch();
  closegraph();
}