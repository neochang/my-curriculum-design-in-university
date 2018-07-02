/////////////////***************************////////////////////////
// This program includes the implementation of the algorithm of
// Scan_Fill.
////////////////***************************////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

typedef struct tagEDGE
     {
       int cyMax;
       float cxBottom;
       float deltaX;
       struct tagEDGE *pNextEdge;
     }EDGE;
typedef struct tagEDGETABLE
     {
       int cyMin;
       int cyMax;
       EDGE* *pTableItems;
     }EDGETABLE;

typedef struct tagPOINT
     {
       int cx;
       int cy;
     }POINT;

EDGETABLE CreateEdgeTable(POINT *pPolygonVertaxes,int nVertaxCount);
EDGE * InsertEdgeToAEL(EDGETABLE EdgeTable, int cyIndex,EDGE *pAEL);
void FilledPolygon(POINT *pPolygonVertaxes,int nVertaxCount);

void main()
{
 // int d[]={160,50,115,75,115,125,160,150,205,125,205,75,160,50};
  int d[40];
  int i,j,n;
  POINT pPolygonVertaxes[20];
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
    printf("\n  X[%d]:",i+1);
    scanf("%d",&pPolygonVertaxes[i].cx);
    printf("\n  Y[%d]:",i+1);
    scanf("%d",&pPolygonVertaxes[i].cy);
    i++;
  }while(i<n);
  /////////************************
  i=0;j=0;
  do
  {
    d[j]=pPolygonVertaxes[i].cx;
    j++;
    d[j]=pPolygonVertaxes[i].cy;
    j++;
    i++;
  }while(i<n);
  d[j]=pPolygonVertaxes[0].cx;
  j++;
  d[j]=pPolygonVertaxes[0].cy;
  ////******************************
  printf("\n  All data collected, Press any key to continue...");
  getch();

/*  do
  {
    pPolygonVertaxes[i].cx=d[j];
    j++;
    pPolygonVertaxes[i].cy=d[j];
    j++;
    i++;
  }while(j<14);  */

  initgraph(&graphdrive,&graphmode,"");
  cleardevice(); setcolor(10);
//  drawpoly(7,d); // Draw Polygon
  drawpoly(n+1,d); // Draw Polygon
  setcolor(14);
//  FilledPolygon(pPolygonVertaxes,7);
  FilledPolygon(pPolygonVertaxes,n);
  getch();
  closegraph();
}  // end main()
////////***********************************************************
EDGETABLE CreateEdgeTable(POINT *pPolygonVertaxes,int nVertaxCount)
{
  int i;
  EDGETABLE EdgeTable;
  int nLineCount;
  EdgeTable.cyMin =EdgeTable.cyMax=pPolygonVertaxes[0].cy;
  for(i=1;i<nVertaxCount;i++)
     {
       if(EdgeTable.cyMin>pPolygonVertaxes[i].cy)
	    EdgeTable.cyMin=pPolygonVertaxes[i].cy;
       if(EdgeTable.cyMax<pPolygonVertaxes[i].cy)
	     EdgeTable.cyMax=pPolygonVertaxes[i].cy;
     }
  nLineCount=EdgeTable.cyMax-EdgeTable.cyMin+1;
  EdgeTable.pTableItems=(EDGE * *)malloc(sizeof(EDGE *)*nLineCount);
  for(i=0;i<nLineCount;i++)
  {
    EdgeTable.pTableItems[i]=NULL;
  }
  for(i=0;i<nVertaxCount;i++)
  {
    int cx0,cy0,cx1,cy1;
    cx0=pPolygonVertaxes[i].cx;
    cy0=pPolygonVertaxes[i].cy;
    cx1=(i<nVertaxCount-1)?pPolygonVertaxes[i+1].cx:pPolygonVertaxes[0].cx;
    cy1=(i<nVertaxCount-1)?pPolygonVertaxes[i+1].cy:pPolygonVertaxes[0].cy;
    if(cy0!=cy1)
    {
      EDGE *pNewEdge;
      int nEdgeTableIndex;
      float deltaX=(float)(cx1-cx0)/(cy1-cy0);
      if(cy1<cy0)
      {
	int k;
	k=cy1;
	cy1=cy0;
	cy0=k;
	cx0=cx1;
      }
      pNewEdge=(EDGE*)malloc(sizeof(EDGE));
      pNewEdge->cyMax=cy1;
      pNewEdge->cxBottom=cx0;
      pNewEdge->deltaX=deltaX;
      pNewEdge->pNextEdge=NULL;
      nEdgeTableIndex=cy0-EdgeTable.cyMin;
      if(EdgeTable.pTableItems[nEdgeTableIndex]==NULL)
         EdgeTable.pTableItems[nEdgeTableIndex]=pNewEdge;
      else
      {
        EDGE *pCurItems=EdgeTable.pTableItems[nEdgeTableIndex];
	while(pCurItems->pNextEdge)
        {
	 pCurItems=pCurItems->pNextEdge;
	}
	pCurItems->pNextEdge=pNewEdge;
      }  
    }
  }
  return EdgeTable;       
}
EDGE *InsertEdgeToAEL(EDGETABLE EdgeTable,int cyIndex,EDGE *pAEL)
{
 EDGE *pAELTable=pAEL;
 EDGE *pCurAELItem;
 EDGE *pPreAELItem;
 EDGE *pCurEdgeInET=EdgeTable.pTableItems[cyIndex-EdgeTable.cyMin];
 while(pCurEdgeInET)
 {
    if(pAELTable==NULL)
    {
      pAELTable=pCurEdgeInET;
      pCurEdgeInET=pCurEdgeInET->pNextEdge;
      pAELTable->pNextEdge=NULL;
    }
    else
    {
      pCurAELItem=pAELTable;
      pPreAELItem=NULL;
      while(pCurAELItem->cxBottom<pCurEdgeInET->cxBottom)
      {
        pPreAELItem=pCurAELItem;
        pCurAELItem=pCurAELItem->pNextEdge;
        if(pCurAELItem==NULL)
        
          break;
        }
        if(pPreAELItem==NULL)
        {
          EDGE *pTmp=pCurEdgeInET;
          pCurEdgeInET=pCurEdgeInET->pNextEdge;
          pTmp->pNextEdge=pCurAELItem;
	  pAELTable=pTmp;
        }
        else if(pCurAELItem==NULL)
        {
          pPreAELItem->pNextEdge=pCurEdgeInET;
          pCurEdgeInET=pCurEdgeInET->pNextEdge;
          pPreAELItem->pNextEdge->pNextEdge=NULL;
        }
        else
        {
        EDGE *pTmp=pCurEdgeInET;
        pCurEdgeInET=pCurEdgeInET->pNextEdge;
        pTmp->pNextEdge=pCurAELItem;
        pPreAELItem->pNextEdge=pTmp;
        }
    }
 }
 return pAELTable;
}
void FilledPolygon(POINT *pPolygonVertaxes,int nVertaxCount)
{
	  EDGETABLE EdgeTable;
	  EDGE *pAELHead=NULL;
	  int i;
	  EdgeTable=CreateEdgeTable(pPolygonVertaxes,nVertaxCount);
	  for(i=EdgeTable.cyMin;i<EdgeTable.cyMax;i++)
	   {
	     EDGE *pCurEdge;
	     EDGE *pPreviousEdge=NULL;
	     if(EdgeTable.pTableItems[i-EdgeTable.cyMin])
	      pAELHead=InsertEdgeToAEL(EdgeTable,i,pAELHead);
	     pCurEdge=pAELHead;
	    while(pCurEdge)
	     {
	       if(pCurEdge->cyMax==i)
		{
		  if(pPreviousEdge)
		   {
		      pPreviousEdge->pNextEdge= pCurEdge->pNextEdge;
		      free(pCurEdge);
		     pCurEdge=pCurEdge->pNextEdge;
		   }
		  else
		   {
		    pAELHead= pCurEdge->pNextEdge;
		    free(pCurEdge);
		    pCurEdge=pAELHead;
		   }
		     }

		   else
		    {
		       pPreviousEdge=pCurEdge;
		       pCurEdge=pCurEdge-> pNextEdge;
		   }
		  }
		pCurEdge=  pAELHead;
	       if( pAELHead)
		 {
		       while(pCurEdge&& pCurEdge-> pNextEdge)
		       {
               line(pCurEdge->cxBottom,i,pCurEdge-> pNextEdge->cxBottom,i);
               getch();
  	           pCurEdge->cxBottom+=pCurEdge->deltaX;
		       pCurEdge->  pNextEdge->cxBottom+= pCurEdge-> pNextEdge->deltaX;
		       pCurEdge=pCurEdge-> pNextEdge->pNextEdge;
	           }
        }
	   }
}