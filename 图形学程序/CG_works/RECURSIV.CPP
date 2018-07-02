/////////////////***************************////////////////////////
// This program includes the implementation of the algorithm of
// Recursive_Fill.
////////////////***************************////////////////////////

#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void FloodFill4(int x,int y,int oldcolor,int newcolor)
{
   if(getpixel(x,y)==oldcolor)
   {
     putpixel(x,y,newcolor);
     getch();
     FloodFill4(x,y+1,oldcolor,newcolor);
     FloodFill4(x,y-1,oldcolor,newcolor);
     FloodFill4(x-1,y,oldcolor,newcolor);
     FloodFill4(x+1,y,oldcolor,newcolor);
    }
}

void BoundaryFill4(int x,int y,int boundarycolor,int newcolor)
{
  int color; color=getpixel(x,y);
  if(color!=newcolor && color!=boundarycolor)
  {
   putpixel(x,y,newcolor);
   getch();
   BoundaryFill4 (x,y+1, boundarycolor,newcolor);
   BoundaryFill4 (x,y-1, boundarycolor,newcolor);
   BoundaryFill4 (x-1,y, boundarycolor,newcolor);
   BoundaryFill4 (x+1,y, boundarycolor,newcolor);
  }
}

void main()
{
  int x_internal=320,y_internal=240;
  int OldColor,NewColor1,NewColor2,BoundaryColor;
//  int pPolygonVertexes[]={315,235,325,235,325,245,315,245,315,235};
  int pPolygonVertexes[]={310,230,330,230,330,250,310,250,310,230};
  int graphdrive=DETECT,graphmode;
  initgraph(&graphdrive,&graphmode,"");
  cleardevice();

  OldColor=getpixel(0,0);
  NewColor1=14;
  NewColor2=9;
  BoundaryColor=10;

  setcolor(10);
  drawpoly(5,pPolygonVertexes); // Draw Polygon

  FloodFill4(x_internal,y_internal,OldColor,NewColor1);
  getch();
  BoundaryFill4(x_internal,y_internal,BoundaryColor,NewColor2);
  getch();
  closegraph();
}