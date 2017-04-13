#include <stdio.h>    
#include <stdlib.h> 
void indexchushi();//从就绪队列取头节点
void output(); //输出状态
void input(); //输入时间 
void printready();//输出就绪队列
void printfinish();//输出完成队列
void PR(); //优先数调度算法

/********************进程控制块PCB****************/
typedef struct node    
{    
	char name[10]; /*进程名*/  
	int cputime;/*CPU运行时间*/        
	int needtime;/*进程运行所需要的时间*/      
	int count;/*记录执行次数*/  
	int pri;  /*进程优先级*/
	char state; /*进程状态*/      
	struct node *next;  
}PCB;    
PCB *ready=NULL,*run=NULL,*finish=NULL;/*定义三个队列*/
int num;    
void createpri(PCB *in); /*创建优先队列*/     
void jiuxu(PCB *in);/*就绪队列尾部*/       
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
		ip->pri=50-ip->needtime;     
		ip->state='W';    
		createpri(ip);      
	}    
} 
/********************输出CPU状态信息****************/ 
void output()        
{    
	PCB *p;    
	p=run;  
	printf("---------------------------------------------------------\n");   
	printf("Name\tcputime\tneedtime count\tpri\tstate\n");
	while(p!=NULL)    
	{   
		printf("%3s\t%4d\t%4d\t%4d\t%2d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->pri,p->state); 
		p=p->next;    
	}  
	p=ready;        
	while(p!=NULL)    
	{    
		printf("%3s\t%4d\t%4d\t%4d\t%2d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->pri,p->state); 
		p=p->next; 
	} 
	p=finish;    
	while(p!=NULL)    
	{    
		printf("%3s\t%4d\t%4d\t%4d\t%2d\t%3c\n",p->name,p->cputime,p->needtime,p->count,p->pri,p->state);   
		p=p->next;}
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
/********************建立优先级队列****************/
void createpri(PCB *in) 
{    
	PCB *head,*to;    
	head=to=ready;    
	if(ready==NULL) 
	{    
		in->next=ready;    
		ready=in;    
	}    
	else     
	{    
		if(in->pri>=head->pri)  
		{    
			in->next = ready;    
			ready=in;    
		}    
		else    
		{    
			while(head->next!=NULL) 
			{    
				to=head;    
				head=head->next;    
			}    

			if(head->next==NULL) 
			{    
				in->next=head->next;    
				head->next=in;    
			}    
			else    
			{    
				to=in;    
				in->next=head;    
			}    
		}    
	}    
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
		while(one->next!=NULL)    
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
/********************优先级调度算法****************/
void PR()   
{    
	int c=1;    
	indexchushi();    
	while(run!=NULL)  
	{    
		output();   
		while(c)    
		{    
			run->pri-=3; 
			run->cputime++;  
			run->needtime--;
			if(run->needtime==0)
			{    
				run->state= 'F';    
				run->count++; 
				wancheng(run);    
				c=0;    
			}    
			else      
			{    
				run->state='W';    
				run->count++; 
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
	printf("【优先数调度算法演示】\n");
	printf("学号：1512440234 姓名：侯圆圆\n\n");
	printf("input the number of processes:");
	scanf("%d",&num);
	input();    
	PR();        
	output();    
}    
