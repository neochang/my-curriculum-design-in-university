////////////////////////////////////////////////////////////////////////
///--- BatchPro.CPP---- 多道批处理作业调度模拟程序----#              ///
///本程序模拟了多道批处理系统中作业调度的情况(只考虑了一个CPU的资源) ///
/// Made By:张伟,2004/1/3---2004/1/4                                 ///
////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#define LEN sizeof(JobNode)

typedef struct LNode
{
  int id;                  //作业编号，初始化为0，证明还没有分配id
  int Flag_Runned;         //是否已执行
  int order;               //调度次序
  int TJTime;              //提交时间 (HHMM),要求用户输入
  int TJTime_convert;      //转化为分钟表示的提交时间
  int run_time;            //运行所需时间，要求用户输入
  int wait_time;           //等待时间
  int start_time;          //调度时间
  int turn_time;           //周转时间
  float weight_turn_time;    //带权周转时间  
  struct LNode *next;
}JobNode,*JobList;

int Job_Quantity;  //全局变量，作业数量

//////(1)******* 将时间转化为分钟 *****>>>>>
int Convert_Time(int time)
{
	int minute_time=0,hour=0,minute=0;
	hour=time/100;
	minute=time%100;
	minute_time=hour*60+minute;
	return minute_time;
} // end Convert_time()
//////*********************************<<<<<<<<

//(2)------  接收用户的输入，产生批处理队列 ---->>>>
JobList ListCreate()
{
     JobList L;
     L=(JobList)malloc(LEN);
     L->next=NULL;
     clrscr();
     printf("\n  Please input quantities of Tasks: ");
     scanf("%d",&Job_Quantity);
     for(int i=Job_Quantity;i>0;--i)
     {
       JobList p;
       p=(JobList)malloc(LEN);
       printf("\n  Please input task Arrive time(HHMM)(%d Remains):",i);
       scanf("%d",&p->TJTime);
       printf("\n  Please input the  time  the task needs(minutes):");
       scanf("%d",&p->run_time);
       p->TJTime_convert=Convert_Time(p->TJTime); //将时间转化为分钟形式
       p->id=0;                                   //初始化作业结点.
       p->Flag_Runned=0;
       p->order=0;
       p->wait_time=0;
       p->start_time=0;
       p->turn_time=0;
       p->weight_turn_time=0;
       p->next=L->next;L->next=p;
     }
     return(L);
} // end ListCreat()
/////---------------<<<<<<<<<<<<<<<<<<<<

/////(3)----- 将作业按提交时间(不是输入次序)排序，生成编号，即id --->>>>
void Sort_Job(JobList &L)
{
	JobList p;
	JobList Min_p;     //记录下提交时间最小的作业指针
	int id_number=1;   //为作业分配id时记数
	int j=0,k=0;       //循环记数器
	int Min_TJTime=0;  //记录一轮查找中最小的提交时间
	int H=0,M=0;       //显示作业队列时，用来存放作业提交时间的小时和分钟
	
	id_number=1;j=0;k=0;  //初始化数据。防止用户再次选择运行时出错。
	Min_TJTime=0;H=0;M=0;
	for(j=Job_Quantity;j>0;--j)
	{
		p=L->next;
		
		while(p->id!=0) //从队列头开始找，如已分配id，跳过
		{
		   p=p->next;
		}
		Min_TJTime=p->TJTime_convert; //找到第一个id为0的作业假定它
		Min_p=p;                      //就是提交时间最小的，记录下来
		p=p->next;                    //看是否还有其他更小的。
		
		while(p!=NULL)
		{
		   if((p->id==0)&&((p->TJTime_convert)<Min_TJTime))
		   {
		     Min_TJTime=p->TJTime_convert;
		     Min_p=p;
		     p=p->next;
		   }
		   else
		   {
		     p=p->next;
		   }
	        }  // end while()
	        
	        //上面while()循环之后，已找到提交时间最早的，但还要看是不是
	        //还有和这个提交时间最早的作业提交时间相同，但运行所需时间
	        //更小的作业，有的话，应重新修改Min_p指针，以保证遵守
	        //“短作业优先”原则
	        p=L->next;
	        while(p!=NULL)
	        {
	          if((p->id==0)&&(p->TJTime_convert==Min_p->TJTime_convert)
	               &&(p->run_time<Min_p->run_time))
	           {
	           	Min_p=p;
	           }
	           p=p->next;
	        }
	        //到此，Min_p是提交时间最早且运行时间最短的作业了，
	        //分配id即可，如下：
	        Min_p->id=id_number;
	        id_number++;
	        
	}   // end for()
	// for 循环之后每个作业都已有id号,以下将结果输出
	clrscr();
	printf("\n  All tasks entered.");
	printf("\n  Now,the Queue of Tasks are as follows:");
	printf("\n  (Sorted by the time they arrived)");
	printf("\n  ==========================================");
	printf("\n  ID    ARRIVE TIME      SERVICE TIME NEEDED");
	printf("\n  ------------------------------------------");
	id_number=1;  //初始化,从id为1的作业开始输出。
	for(k=Job_Quantity;k>0;--k)
	{
	  p=L->next;    //第一个作业

	  while(p->id!=id_number)
	  {
	     p=p->next;
	  }            //如id不符，则找下一个，定能找到符合的作业
	  H=p->TJTime/100;
	  M=p->TJTime%100;
	  printf("\n  %d     %d:%d             %d MINUTES",p->id,H,M,p->run_time);
	  id_number++;
	  if(id_number%15==0)
	  {
	    printf("\n  Press any key to continue....");
	    getch();
	  }
	}
	printf("\n  ==========================================");
}      // end Sort_Job
////*******************<<<<<<<<<<<<

//////(4)--- Process(),对作业进行处理 ----->>>>>>>>>>>
void Process(JobList &L)
{
	int CurrentSysTime=0;  //以分钟形式表示
	int DispatchOrder=1;   //调度次序号
	float Max_Priority;    //记录最高优先权
	float Cur_Priority;    //暂时记录当前计算的优先权
	JobList Max_p;         //记录优先权最高的作业指针
	JobList p;
	
	clrscr();
	printf("\n  Processing,Please wait.....");
	printf("\n  ");
	for(int j=0;j<30;j++)
	{
	  printf(">");
	  delay(150);
	}
	CurrentSysTime=0;  //以分钟形式表示,设系统启动时间为0，即00:00
	DispatchOrder=1;
	Max_Priority=0;
	Max_p=NULL;
	
	p=L->next;          //从链表头开始，查找id为1的作业
	while(p->id!=1)
	{
	    p=p->next;
	}
	//第一个作业一定先执行，而且提交后立即执行。
	CurrentSysTime=p->TJTime_convert;       //系统运行到第一个作业到达
	p->order=DispatchOrder;                 //将调度次序号给作业
	p->Flag_Runned=1;                       //标记为已处理
	p->start_time=p->TJTime;                //提交时间即为调度时间
	p->wait_time=0;                         //等待时间为0
	p->turn_time=p->wait_time+p->run_time;  //周转时间
	p->weight_turn_time=(float)p->turn_time/(float)p->run_time;
	CurrentSysTime=CurrentSysTime+p->run_time; //(#)
	DispatchOrder++;
	
	for(int i=Job_Quantity-1;i>0;--i)
       {
	p=L->next;      //再次从链表头开始
	while((p!=NULL)&&((p->Flag_Runned==1)||(p->TJTime_convert>CurrentSysTime)))
	{
	    p=p->next;
	}             //若不是链表尾，且作业已运行，或作业提交时间在当前时间
	              //之后，则继续找下一个。循环过后，p指向第一个在当前时间
	              //之前到达且未被处理的作业，或p指向NULL.
	              
	if(p==NULL)      //p=NULL证明在当前时间之前没有到达新的作业，
	{  // if(1)     //则直接取下一个id=DispatchOrder的作业.
	   p=L->next;
	   while(p->id!=DispatchOrder)
	   {
	     p=p->next;
	   }
	   CurrentSysTime=p->TJTime_convert;       //系统运行到此作业到达
	   p->order=DispatchOrder;                 //将调度次序号给作业
	   p->Flag_Runned=1;                       //标记为已处理
	   p->start_time=p->TJTime;                //提交时间即为调度时间
	   p->wait_time=0;                         //等待时间为0
	   p->turn_time=p->wait_time+p->run_time;  //周转时间
	   p->weight_turn_time=(float)p->turn_time/(float)p->run_time;
	   CurrentSysTime=CurrentSysTime+p->run_time;
	   DispatchOrder++;
	}  // end if(1)
	else          //p!=NULL,证明在当前时间之前又有新作业到达，记算优先权
	{  // else(1) //假定它就是优先权最高的
	   Max_p=p;
	   p->wait_time=CurrentSysTime-p->TJTime_convert;
	   Max_Priority=(float)(p->wait_time+p->run_time)/(float)p->run_time;
	   p=p->next; 
	   //下面的while()循环看是否还有在当前时间前到达且优先权更高的>>>
	   while(p!=NULL)
	   {
	    if((p->TJTime_convert<CurrentSysTime)&&(p->Flag_Runned==0))
	    { // if(2): 如果在当前时间前到达且未运行，则计算优先权
	      p->wait_time=CurrentSysTime-p->TJTime_convert;
	      Cur_Priority=(float)(p->wait_time+p->run_time)/(float)p->run_time;
	        if(Cur_Priority>Max_Priority)
	        { // if(3): 计算出的优先权比原来的大，则以当前的作业
	          //        做为新的优先权最高的作业
	      	   Max_Priority=Cur_Priority;
	      	   Max_p=p;
	      	   p=p->next;
	        } // end if(3)
	        else
	        { // else(3): 不如原来的优先权大，仍不替换，看下一个
	       	   p=p->next;
	        } // end else(3)
	    } //end if(2)
	    else
	    { // else (2):不是在当前时间以前到达的或已运行，则看下一个
	      p=p->next;
	    } // end else(2)
	   } // end while()
	   
	   //while()循环过后，Max_p已指向优先权最高的作业，执行即可.
	   //现在的系统时间还是上一个作业执行完的时间，即为(#)标记处的时间
	   //也就是说中间选择作业的过程所用时间忽略不计:
	   
	   Max_p->order=DispatchOrder;                 //将调度次序号给作业
	   Max_p->Flag_Runned=1;                       //标记为已处理	   
	   Max_p->start_time=                          //调度时间为当前系统时间
	      (CurrentSysTime/60)*100+(CurrentSysTime%60);
	   Max_p->wait_time=CurrentSysTime-Max_p->TJTime_convert;
	   Max_p->turn_time=Max_p->wait_time+Max_p->run_time;  //周转时间
	   Max_p->weight_turn_time=(float)Max_p->turn_time/(float)Max_p->run_time;
	   CurrentSysTime=CurrentSysTime+Max_p->run_time;
	   DispatchOrder++;
	} // end else(1)
       } // end for(int i=Job_Quantity-1;i>0;--i)
}  // end Process()
//////**********************************<<<<<<<<<<<

//////(5)******* 打印处理后的结果 *********>>>>>>>>>>>
void Print_Result(JobList &L)
{
	int ExecuteOrder;
	int start_time_HOUR,start_time_MINUTE;
	int TJTime_HOUR,TJTime_MINUTE;
	float Ave_Turnover_Time;
	float Ave_WTurnover_Time;
	JobList p;
	
	ExecuteOrder=1;
	start_time_HOUR=0;
	start_time_MINUTE=0;
	TJTime_HOUR=0;
	TJTime_MINUTE=0;
	Ave_Turnover_Time=0.0;
	Ave_WTurnover_Time=0.0;
	
	printf("\n  Completed!");
	printf("\n  The result is:");
	printf("\n================================================================================");
	printf("\nDISPATCH_ORDER  ID  ARRIVE_TIME  START_TIME  TURNOVER_TIME  WEIGHT_TURNOVER_TIME");
	printf("\n--------------------------------------------------------------------------------");
	for(int t=Job_Quantity;t>0;--t)
	{
	  p=L->next;    //第一个作业

	  while(p->order!=ExecuteOrder)
	  {
	     p=p->next;
	  }
	  start_time_HOUR=p->start_time/100;
	  start_time_MINUTE=p->start_time%100;
	  TJTime_HOUR=p->TJTime/100;
	  TJTime_MINUTE=p->TJTime%100;
	  printf("\n   %d            %d     %d:%d        %d:%d       %d MINUTES         %-6.2f",
	         p->order,p->id,TJTime_HOUR,TJTime_MINUTE,start_time_HOUR,start_time_MINUTE,
	         p->turn_time,p->weight_turn_time);
	  ExecuteOrder++;
	  if(ExecuteOrder%15==0)
	  {
	    printf("\n  Press any key to continue....");
	    getch();
	  }
	}
	printf("\n================================================================================");
	
	//计算平均周转时间:
	//-----------------
	p=L->next;
	for(int m=Job_Quantity;m>0;--m)
	{
	  Ave_Turnover_Time=Ave_Turnover_Time+(float)p->turn_time;
	  p=p->next;
	}
	Ave_Turnover_Time=Ave_Turnover_Time/Job_Quantity;
	
	//计算平均带权周转时间:
	//---------------------
	p=L->next;
	for(int n=Job_Quantity;n>0;--n)
	{ 
	  Ave_WTurnover_Time=Ave_WTurnover_Time+(float)p->weight_turn_time;
	  p=p->next;
	}
	Ave_WTurnover_Time=Ave_WTurnover_Time/Job_Quantity;
	
	printf("\n  STATISTIC RESULTS:");
	printf("\n **********************************************");
	printf("\n  Average    Turnover     Time: %-6.2f MINUTES",Ave_Turnover_Time);
	printf("\n  Average Weight Turnover Time: %-6.2f MIN/MIN",Ave_WTurnover_Time);
	printf("\n **********************************************");
	printf("\n\n  Press any key to continue....");
	getch();
} // end Print_Result()
/////////*******************************<<<<<<<<<<<

//////// Main Function >>>>>>>>>>
void main()
{
	JobList L;
	char SEL;

	while(1)
       {
	clrscr();    //清屏
	printf("\n            **********************************************");
	printf("\n            This program simulates the Task Dispatching of");
	printf("\n            Multiprogrammed Batch Processing System.");
	printf("\n                                        Made By:ZhangWei\n");
	printf("\n                   PRESS 1 TO START OR PRESS 0 TO EXIT");
	printf("\n                   -----------------------------------");
	printf("\n                     1. Start to input tasks");
	printf("\n                     0. EXIT");
	printf("\n                   -----------------------------------");
	printf("\n                                     Your selection is:");
	scanf("%c",&SEL);
	switch(SEL)
	{
	case '1' :
	 {
	  L=(JobList)malloc(LEN);
	  L=ListCreate();        //接收输入的作业队列
	  Sort_Job(L);           //以提交时间为序,为作业分配id.
	  printf("\n\n  Press any key to execute the tasks...");
	  getch();
	  Process(L);
	  Print_Result(L);
	  break;
	 }  // end case 1
	case '0' : exit(0);
	default: break;
	} // end switch(SEL)
       } //  end while(1)
} // end main()
////////////////////////////////
