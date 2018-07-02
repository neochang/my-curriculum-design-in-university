/////////********************************************************///////////
///// This program includes the implementation of the following algorithms:
///// "Middle Point Circle","Bresenham Circle","DDA Line","Middle Point Line",
///// "Bresenham Line". And the algorithms of Line Style and Line Width are
///// also implemented.
/////--------------------------------------------------------------
///// Author:         ZhangWei
///// Creat Date:     2003-09-06
///// Last Modified:  2003-09-14
/////////********************************************************///////////

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

void PrintColorSelectionTable(void);
void MidPointCircle(int,int,int,int);
void BresenhamCircle(int,int,int,int);
void swap(int *p1,int *p2);
void DDALine(int,int,int,int,int,int,int);
void MidPointLine(int,int,int,int,int,int,int);
void BresenhamLine(int,int,int,int,int,int,int);

//******The Main Function****>>>
void main()
{
     int graphdrive=DETECT,graphmode;
     int GraphSelect=0,AlgorithmSelect=0;
     int Color=14;
     int x0=0,y0=0,Radius=200;// Parameters of Circle
     int x1=0,y1=0,x2=640,y2=480;//Parameters of Line
     int linestyle=1,linewidth=1;

	       printf(">>>*********************************************>>>\n");
 graph_select: printf("  Please select the graphics you want [Enter ""1,2,3"" to select]:");
	       printf("\n\n  1. CIRCLE   2.LINE");
	       printf("\n\n  Your selection is:");
	       scanf("%d",&GraphSelect);

 switch(GraphSelect)
 {
  case 1 : {
	    printf("  You have selected to draw a CIRCLE.\n");
	    printf("  Please input the Center Coordinates of the Cirle:");
	    printf("\n  X0:");
	    scanf("%d",&x0);
	    printf("  Y0:");
	    scanf("%d",&y0);
	    printf("\n  Please input the Radius of the Circle:");
	    printf("\n  Radius:");
	    scanf("%d",&Radius);
	    PrintColorSelectionTable();
	    scanf("%d",&Color);
	    //--------- Algorithm Selection (Circle) >>>
   alg_cir: printf("\n  Please select the algorithm you want to use:");
	    printf("\n  1.Middle Point Circle   2.Bresenham Circle");
	    printf("\n  Your selection is:");
	    scanf("%d",&AlgorithmSelect);
	    if((AlgorithmSelect!=1)&&(AlgorithmSelect!=2))
	     {
	      printf("  ---------INPUT ERROR!!----------\n\n");
	      goto alg_cir;
	     }
	    //-------------------------
	    printf("\n  All data collected,Press any key to start...");
	    getch();
	    initgraph(&graphdrive,&graphmode,"");
	    cleardevice();
	    if (AlgorithmSelect==1)
	      {
		MidPointCircle(x0,y0,Radius,Color);// Middle Point Circle
	      }
	    else if (AlgorithmSelect==2)
	      {
		BresenhamCircle(x0,y0,Radius,Color);// Bresenham Circle
	      }
	    getch();
	    circle(x0,getmaxy()-y0,Radius);
	    getch();
	    closegraph();
	 } break; // end case 1 ****************************
  case 2 : {
	    printf("  You have selected to draw a LINE.\n");
	    printf("  Please input the coordinates of the Starting Point and End Point:");
	    printf("\n  X1:");
	    scanf("%d",&x1);
	    printf("  Y1:");
	    scanf("%d",&y1);
	    printf("  X2:");
	    scanf("%d",&x2);
	    printf("  Y2:");
	    scanf("%d",&y2);
	    PrintColorSelectionTable();
	    scanf("%d",&Color);
	    //--------- Line Style Selection >>>
 style_sel: printf("\n  Please select the Style of the Line:");
	    printf("\n  1.Solid Line         2.Long Dashed Line");
	    printf("\n  3.Short Dashed Line  4.Dashdotted Line");
	    printf("\n  Your selection is:");
	    scanf("%d",&linestyle);
	    if((linestyle!=1)&&(linestyle!=2)&&(linestyle!=3)&&(linestyle!=4))
	     {
	      printf("  ---------INPUT ERROR!!----------\n\n");
	      goto style_sel;
	     }
	    //------------------------------
	    printf("\n  Please input the Width of the Line:");
	    printf("\n  Width:");
	    scanf("%d",&linewidth);
	    //--------- Algorithm Selection (Line) >>>
  alg_line: printf("\n  Please select the algorithm you want to use:");
	    printf("\n  1.DDA Line  2.Middle Point Line  3.Bresenham Line");
	    printf("\n  Your selection is:");
	    scanf("%d",&AlgorithmSelect);
	    if((AlgorithmSelect!=1)&&(AlgorithmSelect!=2)&&(AlgorithmSelect!=3))
	     {
	      printf("  ---------INPUT ERROR!!----------\n\n");
	      goto alg_line;
	     }
	    //------------------------------
	    printf("\n  All data collected,Press any key to start...");
	    getch();
	    initgraph(&graphdrive,&graphmode,"");
	    cleardevice();
	    if (AlgorithmSelect==1)
	      {
		DDALine(x1,y1,x2,y2,Color,linestyle,linewidth);// DDA Line
	      }
	    else if (AlgorithmSelect==2)
	      {
	       MidPointLine(x1,y1,x2,y2,Color,linestyle,linewidth);// Middle Point Line
	      }
	    else if (AlgorithmSelect==3)
	      {
	      	BresenhamLine(x1,y1,x2,y2,Color,linestyle,linewidth);// Bresenhan Line
	      }
	    MidPointCircle(x1,y1,linewidth+2,Color);  //  Mark the Stating Point.
	    BresenhamCircle(x2,y2,linewidth+2,Color); //  Mark the End Point.
	    getch();
	    line(x1,getmaxy()-y1,x2,getmaxy()-y2);
	    getch();
	    closegraph();
	   } break;  // end case 2 ************************
  default :{
	    printf("  ---------INPUT ERROR!!----------\n\n");
	    goto graph_select;
	   }
 } // end switch
} // end main()

///********Print color selection table*******>>>
void PrintColorSelectionTable()
{
  printf("\n  Please select the Color of the Graphic:");
  printf("\n  **********************************************************");
  printf("\n   0.BLACK       1.BLUE           2.GREEN        3.CYAN");
  printf("\n   4.RED         5.MAGENTA        6.BROWN        7.LIGHTGRAY");
  printf("\n   8.DARKGRAY    9.LIGHTBLUE     10.LIGHTGREEN  11.LIGHTCYAN");
  printf("\n  12.LIGHTTRED  13.LIGHTMAGENTA  14.YELLOW      15 WHITE");
  printf("\n  **********************************************************");
  printf("\n  Color:");
}  // end PrintColorSelectionTable()

//-----------swap()------>>>
void swap(int *p1,int *p2)
{
  int temp;
  temp=*p1;
  *p1=*p2;
  *p2=temp;
} // end swap()

//**********The Functions of drawing the graphics*****>>>
void MidPointCircle(int x0,int y0,int Radius,int Color)
{
 int CurrentX=0;
 int CurrentY=Radius;
 int d=3-2*Radius;
 do
 {
   putpixel(CurrentX+x0,getmaxy()-(CurrentY+y0),Color);
   putpixel(-CurrentX+x0,getmaxy()-(-CurrentY+y0),Color);
   putpixel(-CurrentX+x0,getmaxy()-(CurrentY+y0),Color);
   putpixel(CurrentX+x0,getmaxy()-(-CurrentY+y0),Color);
   putpixel(CurrentY+x0,getmaxy()-(CurrentX+y0),Color);
   putpixel(-CurrentY+x0,getmaxy()-(-CurrentX+y0),Color);
   putpixel(-CurrentY+x0,getmaxy()-(CurrentX+y0),Color);
   putpixel(CurrentY+x0,getmaxy()-(-CurrentX+y0),Color);
   if(d<0)
     d+=4*CurrentX+6;
   else
    {
      d+=4*(CurrentX-CurrentY)+10;
      CurrentY--;
    }
    CurrentX++;
 } while(CurrentX<CurrentY);
} // end MidPointCircle()

//-----------------------------------
void BresenhamCircle(int x0,int y0,int Radius,int Color)
{
  int x,y,delta,delta1,delta2,direction; //Here x,y is equal to CurrentX,CurrentY in MidPointCircle().
  x=0;y=Radius;
  delta=2*(1-Radius);
  while(y>=0)
    {
     putpixel(x+x0,getmaxy()-(y+y0),Color);
     putpixel(x+x0,getmaxy()-(-y+y0),Color);
     putpixel(-x+x0,getmaxy()-(y+y0),Color);
     putpixel(-x+x0,getmaxy()-(-y+y0),Color);
     if(delta<0)
       {
	delta1=2*(delta+y)-1;
	  if(delta1<=0) direction=1;
	  else direction=2;
       }
     else if(delta>0)
       {
	delta2=2*(delta-x)-1;
	  if(delta2<=0) direction=2;
	  else direction=3;
       }
     else direction=2;
  switch(direction)
     {
      case 1: x++;delta+=2*x+1;break;
      case 2: x++;y--;delta+=2*(x-y+1);break;
      case 3: y--;delta+=(-2*y+1);break;
     }
    } //end while
} // end BresenhamCircle()

//-----------------------------
void DDALine(int x1,int y1,int x2,int y2,int Color,int linestyle,int linewidth)
{
  int *pointer_x1,*pointer_x2,*pointer_y1,*pointer_y2;
  int X=0,Y=0,X_internal=0;
  int CurrentX,CurrentYY;
  int n=0;   //            Count the pixels to draw.
  int i=1;
  float CurrentY,CurrentXX,Y_internal;
  unsigned int mark=0x8000;
  unsigned int style=0xFFFF;

  switch(linestyle)
  {
   case 1 : style=0xFFFF;break;
   case 2 : style=0xFF00;break;
   case 3 : style=0xF0F0;break;
   case 4 : style=0x6F6F;break;
  }

  pointer_x1=&x1;pointer_x2=&x2;
  pointer_y1=&y1;pointer_y2=&y2;

  if(x1==x2)
    {
     X=x1;
     if(y1<y2)
	for(Y=y1;Y<=y2;Y++)
	 {
	  n++;
	  if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
	  if (n%16==1) mark=0x8000;           // The first point of the line
	  if (n%16==0) mark=0x0001;           // The last point of the line
	  if (style&mark)
	     {
	      putpixel(X,getmaxy()-Y,Color);
	      if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=X;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-Y,Color);
		 X_internal++;
		}
		X_internal=X;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-Y,Color);
		 X_internal--;
		}
	       }
	       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=X;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-Y,Color);
		 X_internal++;
		}
		X_internal=X;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-Y,Color);
		 X_internal--;
		}
	       }
	     }
	 }
     else if(y1>=y2)
	for(Y=y2;Y<=y1;Y++)
	 {
	  n++;
	  if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
	  if (n%16==1) mark=0x8000;           // The first point of the line
	  if (n%16==0) mark=0x0001;           // The last point of the line
	  if (style&mark)
	  {
	   putpixel(X,getmaxy()-Y,Color);
	   if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=X;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-Y,Color);
		 X_internal++;
		}
		X_internal=X;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-Y,Color);
		 X_internal--;
		}
	       }
	       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=X;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-Y,Color);
		 X_internal++;
		}
		X_internal=X;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-Y,Color);
		 X_internal--;
		}
	       }
	  }
	 }
    } // end x1=x2
  else //******** x1!=x2**********
 {
  int deltaX=x2-x1;
  int deltaY=y2-y1;
  float Slope=(float)deltaY/(float)deltaX;

  if(((Slope>=-1)&&(Slope<0)) || ((Slope>=0)&&(Slope<=1)))
  {  // ***** |k|<=1 ***** Increase Y to achieve line width
      if(x1>x2)    // To keep x1<x2, CurrentY increase as CurrentX increased.
    {
     swap(pointer_x1,pointer_x2);
     swap(pointer_y1,pointer_y2);
    }

   CurrentY=(float)y1;
   for(CurrentX=x1;CurrentX<=x2;CurrentX++)
    {
     n++;
     if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
     if (n%16==1) mark=0x8000;           // The first point of the line
     if (n%16==0) mark=0x0001;           // The last point of the line
     if (style&mark)
      {
       putpixel(CurrentX,getmaxy()-(int)(CurrentY+0.5),Color);
       if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(int)(Y_internal+1+0.5),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(int)(Y_internal-1+0.5),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(int)(Y_internal+1+0.5),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(CurrentX,getmaxy()-(int)(Y_internal-1+0.5),Color);
		 Y_internal--;
		}
	       }
      }
     CurrentY+=Slope;
    }
  } // end |k|<=1
  else if((Slope<-1) || (Slope>1))
  { //******* |k|>1 ******** Increase X coordinate to achieve line width
      if(y1>y2)   // To keep y1<y2,CurrentXX increase as CurrentYY increased.
    {
     swap(pointer_y1,pointer_y2);
     swap(pointer_x1,pointer_x2);
    }

   CurrentXX=(float)x1;
   for(CurrentYY=y1;CurrentYY<=y2;CurrentYY++)
    {
     n++;
     if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
     if (n%16==1) mark=0x8000;           // The first point of the line
     if (n%16==0) mark=0x0001;           // The last point of the line
     if (style&mark)
      {
       putpixel((int)(CurrentXX+0.5),getmaxy()-CurrentYY,Color);
       if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=CurrentXX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentYY,Color);
		 X_internal++;
		}
		X_internal=CurrentXX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentYY,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=CurrentXX;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentYY,Color);
		 X_internal++;
		}
		X_internal=CurrentXX;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentYY,Color);
		 X_internal--;
		}
	       }
      }
     CurrentXX+=1/Slope;
    }
  } // end |k|>1
 } // end else (x1!=x2)
} // end DDALine()

//-----------------------------
void MidPointLine(int x0,int y0,int x1,int y1,int Color,int linestyle,int linewidth)
{
  int t=0;

  if((x0>x1)&&(y0>y1))
      {
	t=x0;x0=x1;x1=t;
	t=y0;y0=y1;y1=t;
      }
 if((x0>x1)&&(y0<y1))
     {
       t=x0;x0=x1;x1=t;
       t=y0;y0=y1;y1=t;
     }

  //int deltaX=x1-x0;
  //int detalY=y1-y0;
  int a=y1-y0;
  int b=x1-x0;
  int d0=-2*a+b;   //0<k<1
  int d1=a-2*b;     //k>=1
  int d2=-a-2*b;   //k<=-1
  int d3=2*a+b;     //-1<k<0
  int CurrentX=x0;
  int CurrentY=y0;
  int X_internal=0;
  int Y_internal=0;
  int IncreaseNE0=2*(-a+b);
  int IncreaseE0=-2*a;             //0<k<1
  int IncreaseNE1=2*(a-b);
  int IncreaseE1=-2*b;       //k>=1
  int IncreaseNE2=-2*(a+b);
  int IncreaseE2=-2*b;             //k<=-1
  int IncreaseNE3=2*(a+b);
  int IncreaseE3=2*a;              //-1<k<0
  int n=0;   //            Count the pixels to draw.
  int i=1;
  unsigned int mark=0x8000;
  unsigned int style=0xFFFF;

  switch(linestyle)
  {
   case 1 : style=0xFFFF;break;
   case 2 : style=0xFF00;break;
   case 3 : style=0xF0F0;break;
   case 4 : style=0x6F6F;break;
  }

 if(y1==y0)    //k=0
  {
    for(CurrentX=x0;CurrentX<=x1;CurrentX++)
     {
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
        putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       }
     }
  }
  else if(x1==x0)
  {
    for(CurrentY=y0;CurrentY<=y1;CurrentY++)
     {
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
        putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=CurrentX;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       }
     }
  }
 else  // x0!=x1 and y0!=y1
 {
  float Slope=(float)a/(float)b;
  if((Slope>0)&&(Slope<1))
  {
   do{
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
	putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       }

      if(d0>=0)
	d0+=IncreaseE0;
      else
      {
	d0+=IncreaseNE0;
	CurrentY++;
      }
	CurrentX++;
    }while(CurrentX<=x1);
  }

  if(Slope>=1)
  {
   do{
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
	putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=CurrentX;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       }

      if(d1>=0)
	d1+=IncreaseE1;
      else
      {
	d1+=IncreaseNE1;
	CurrentX++;
      }
	CurrentY++;
    }while(CurrentY<=y1);
  }

  if(Slope<=-1)
  {
   do{
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
	putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=CurrentX;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(X_internal+1,getmaxy()-CurrentY,Color);
		 X_internal++;
		}
		X_internal=CurrentX;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(X_internal-1,getmaxy()-CurrentY,Color);
		 X_internal--;
		}
	       }
       }

      if(d2>=0)
	d2+=IncreaseE2;
	else
	{
	  d2+=IncreaseNE2;
	  CurrentX++;
	}
	  CurrentY--;
      }while(CurrentY>=y1);
    }

  if((Slope>-1)&&(Slope<0))
  {
   do{
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
       {
	putpixel(CurrentX,getmaxy()-CurrentY,Color);
        if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=(linewidth-1)/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=CurrentY;
		for(i=1;i<=linewidth/2;i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=CurrentY;
		for(i=1;i<=((linewidth/2)-1);i++)
		{
		 putpixel(CurrentX,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       }

      if(d3>=0)
	d3+=IncreaseE3;
      else
      {
	d3+=IncreaseNE3;
	CurrentY--;
      }
       CurrentX++;
    }while(CurrentX<=x1);
  }
 } // end  x0!=x1 && y0!=y1
} // end MidPointLine()

//------------------------------------
void BresenhamLine(int x0,int y0,int x1,int y1,int Color,int linestyle,int linewidth)
{
 int t=0;

 if((x0>x1)&&(y0>y1))
      {
	t=x0;x0=x1;x1=t;
	t=y0;y0=y1;y1=t;
      }
 if((x0>x1)&&(y0<y1))
     {
       t=x0;x0=x1;x1=t;
       t=y0;y0=y1;y1=t;
     }
     	
 int x, y, dx, dy,i;
 int X_internal=0;
 int Y_internal=0;
 int  e;
 float k;
 int n=0;   //            Count the pixels to draw.
 int j=1;
 unsigned int mark=0x8000;
 unsigned int style=0xFFFF;

 switch(linestyle)
 {
   case 1 : style=0xFFFF;break;
   case 2 : style=0xFF00;break;
   case 3 : style=0xF0F0;break;
   case 4 : style=0x6F6F;break;
 }

 dx=x1-x0; dy=y1-y0;
 e=-dx; x=x0; y=y0;

 if(x0==x1)
 {
  for(y=y0;y<=y1;y++)
  {
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
      {
       putpixel(x,getmaxy()-y,Color);
       if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=x;
		for(j=1;j<=linewidth/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=((linewidth/2)-1);j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
      }
  }
 }
 else
{
 k=(float)dy/(float)dx;
 if((k<=1)&&(k>=0))
 {
  for (i=0;i<=dx;i++)
   {
      n++;
      if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
      if (n%16==1) mark=0x8000;           // The first point of the line
      if (n%16==0) mark=0x0001;           // The last point of the line
      if (style&mark)
      {
       putpixel(x, getmaxy()-y, Color);
       if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=y;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=y;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=y;
		for(j=1;j<=linewidth/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=y;
		for(j=1;j<=((linewidth/2)-1);j++)
		{
		 putpixel(x,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
      }
       x=x+1;e=e+2*dy;
       if (e>=0)
       { 
       	y++; e=e-2*dx;
       }
   }
 }
 else if(k>1)
 {e=-dy;
  for(i=0;i<=dy;i++)
  {
    n++;
    if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
    if (n%16==1) mark=0x8000;           // The first point of the line
    if (n%16==0) mark=0x0001;           // The last point of the line
    if (style&mark)
    {
     putpixel(x,getmaxy()-y,Color);
     if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=x;
		for(j=1;j<=linewidth/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=((linewidth/2)-1);j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
    }
   y=y+1;e=e+2*dx;
   if(e>=0)
   {
    x++;e=e-2*dy;
   }
  }
 }
 else if((k>=-1)&&(k<0))
 { e=-dx;
   x=x1;y=y1;
   for(i=dx;i>=1;i--)
   {
     n++;
     if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
     if (n%16==1) mark=0x8000;           // The first point of the line
     if (n%16==0) mark=0x0001;           // The last point of the line
     if (style&mark)
     {
      putpixel(x,getmaxy()-y,Color);
      if(linewidth%2!=0)     // linewidth is a odd number
	       {
		Y_internal=y;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=y;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		Y_internal=y;
		for(j=1;j<=linewidth/2;j++)
		{
		 putpixel(x,getmaxy()-(Y_internal+1),Color);
		 Y_internal++;
		}
		Y_internal=y;
		for(j=1;j<=((linewidth/2)-1);j++)
		{
		 putpixel(x,getmaxy()-(Y_internal-1),Color);
		 Y_internal--;
		}
	       }
     }
    x=x-1;e=e-2*dy;
    if(e>=0)
    {y++;e=e-2*dx;}
   }
 }

 else if(k<-1)
 {e=-dy;
  x=x0;y=y0;
  for(i=abs(dy);i>=1;i--)
  {
    n++;
    if (n%16>1) mark=0x8000>>(n%16-1); // The middle point of the line
    if (n%16==1) mark=0x8000;           // The first point of the line
    if (n%16==0) mark=0x0001;           // The last point of the line
    if (style&mark)
    {
     putpixel(x,getmaxy()-y,Color);
     if(linewidth%2!=0)     // linewidth is a odd number
	       {
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=(linewidth-1)/2;j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
       else if(linewidth%2==0) //linewidth is an even number
	       {
		X_internal=x;
		for(j=1;j<=linewidth/2;j++)
		{
		 putpixel(X_internal+1,getmaxy()-y,Color);
		 X_internal++;
		}
		X_internal=x;
		for(j=1;j<=((linewidth/2)-1);j++)
		{
		 putpixel(X_internal-1,getmaxy()-y,Color);
		 X_internal--;
		}
	       }
    }
   y--;e=e-2*dx;  //circle(50,50,20);
   if(e<=0)
   {x++;e=e-2*dy;}
  }
 }
} // end else, x0==x1
} // end BresenhamLine()