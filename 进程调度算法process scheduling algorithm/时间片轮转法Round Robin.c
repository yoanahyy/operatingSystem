#include <stdio.h>  
#include <stdlib.h> 
void indexchushi(); //从就绪队列取头节点  
void output(); //输出状态   
void input(); //输入时间   
void RR();//时间片轮转调度算法
void printready();//输出就绪队列
void printfinish();//输出完成队列

/********************进程控制块PCB****************/
typedef struct node    
{ 
	char name[10];/*进程名*/ 
	char state;/*进程状态*/     
	int cputime;/*CPU运行时间*/  
	int needtime;/*进程运行所需要的时间*/       
	int count;/*记录执行次数*/ 
	int round; /*分配给CPU的时间片*/       
	struct node *next;     
}PCB;    
PCB *ready=NULL,*run=NULL,*finish=NULL; /*定义三个队列*/ 
int num;
void jiuxu(PCB *in);  /*就绪队列尾部*/    
void wancheng(PCB *in); /*完成队列尾部*/  
/********************从就绪队列取头节点****************/ 
void indexchushi()  
{    
	run=ready;    
	if(ready!=NULL)    
	{    
		run->state='R';    
		ready=ready->next;    
		run->next=NULL;    
	}    
}  
/********************输入进程所需时间****************/
void input() 
{    
	PCB *ip;    
	int i;   
	printf("input name and needtime：\n");    
	for(i=0;i<num;i++)    
	{    
		if((ip=(PCB *)malloc(sizeof(PCB)))==NULL)    
		{    
			perror("malloc");    
			exit(1);    
		}    
		scanf("%s",ip->name);    
		getchar();    
		scanf("%d",&(ip->needtime));    
		ip->cputime=0; 
		ip->count=0;       
		ip->round=2;     
		ip->state='W'; 	    
		jiuxu(ip);    
	}    
}    
/********************输出CPU状态信息****************/
void output()    
{    
	PCB *p;    
	p=run;  
	printf("---------------------------------------------------------\n");   
	printf("Name\tcputime\tneedtime count\tround\tstate\n");
	while(p!=NULL)    
	{   
		printf("%3s\t%4d\t%4d\t%4d\t%3d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->round,p->state); 
		p=p->next;    
	}  
	p=ready;        
	while(p!=NULL)    
	{    
		printf("%3s\t%4d\t%4d\t%4d\t%3d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->round,p->state); 
		p=p->next; 
	}
	p=finish;    
	while(p!=NULL)    
	{    
		printf("%3s\t%4d\t%4d\t%4d\t%3d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->round,p->state);   
		p=p->next;    
	}
	printready();
	printfinish();
}    
/********************输出就绪队列****************/
void printready()
{
	PCB *p;
	p=ready;
	printf("就绪队列：");
	while(p!=NULL)    
	{ 
		printf("%s\t",p->name);
		p=p->next;  
	}
	printf("\n");
}
/********************输出完成队列****************/
void printfinish()
{
	PCB *p;
	p=finish;
	printf("完成队列：");
	while(p!=NULL)    
	{ 
		printf("%s\t",p->name);
		p=p->next;  
	}
	printf("\n");
}
/********************进程插入就绪队列最后****************/
void jiuxu(PCB *in)  
{    
	PCB *one;    
	one=ready;    
	if(ready==NULL)    
	{    
		in->next=ready;    
		ready=in;    
	}    
	else    
	{    
		while(one->next!= NULL)    
		{    
			one=one->next;    
		}    
		in->next=one->next;    
		one->next=in;    
	}    
}   
/********************进程插入完成队列最后****************/
void wancheng(PCB *in)  
{    
	PCB *one;    
	one=finish;    
	if(finish==NULL)    
	{    
		in->next=finish;    
		finish=in;    
	}    
	else    
	{    
		while(one->next!= NULL)    
		{    
			one=one->next;    
		}    
		in->next=one->next;    
		one->next=in;    
	}    
}    


/********************时间片轮转调度算法****************/		
void RR()   
{     
	int c=1;       
	indexchushi();    
	while(run!=NULL)    
	{    
		output();    
		while(c)    
		{    
			run->count++;    
			run->cputime++;    
			run->needtime--;    
			if(run->needtime==0)  
			{    
				run->state='F';    
				wancheng(run);    
				c=0;    
			}    
			else if(run->count==run->round)
			{    
				run->state='W';    
				run->count=0;  
				jiuxu(run);    
				c=0;    
			}    
		}    
		c=1;    
		indexchushi();    
	}    
}   
/********************主函数界面****************/
void main()    
{
	printf("【时间片轮转调度算法演示】\n");
	printf("学号：1512440234 姓名：侯圆圆\n\n");
	printf("input the number of processes:");
	scanf("%d",&num);
	input();    
	RR();    
	output();
}    
