#include <stdio.h>  
#include <stdlib.h> 
void indexchushi(); //�Ӿ�������ȡͷ�ڵ�  
void output(); //���״̬   
void input(); //����ʱ��   
void RR();//ʱ��Ƭ��ת�����㷨
void printready();//�����������
void printfinish();//�����ɶ���

/********************���̿��ƿ�PCB****************/
typedef struct node    
{ 
	char name[10];/*������*/ 
	char state;/*����״̬*/     
	int cputime;/*CPU����ʱ��*/  
	int needtime;/*������������Ҫ��ʱ��*/       
	int count;/*��¼ִ�д���*/ 
	int round; /*�����CPU��ʱ��Ƭ*/       
	struct node *next;     
}PCB;    
PCB *ready=NULL,*run=NULL,*finish=NULL; /*������������*/ 
int num;
void jiuxu(PCB *in);  /*��������β��*/    
void wancheng(PCB *in); /*��ɶ���β��*/  
/********************�Ӿ�������ȡͷ�ڵ�****************/ 
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
/********************�����������ʱ��****************/
void input() 
{    
	PCB *ip;    
	int i;   
	printf("input name and needtime��\n");    
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
/********************���CPU״̬��Ϣ****************/
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
/********************�����������****************/
void printready()
{
	PCB *p;
	p=ready;
	printf("�������У�");
	while(p!=NULL)    
	{ 
		printf("%s\t",p->name);
		p=p->next;  
	}
	printf("\n");
}
/********************�����ɶ���****************/
void printfinish()
{
	PCB *p;
	p=finish;
	printf("��ɶ��У�");
	while(p!=NULL)    
	{ 
		printf("%s\t",p->name);
		p=p->next;  
	}
	printf("\n");
}
/********************���̲�������������****************/
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
/********************���̲�����ɶ������****************/
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


/********************ʱ��Ƭ��ת�����㷨****************/		
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
/********************����������****************/
void main()    
{
	printf("��ʱ��Ƭ��ת�����㷨��ʾ��\n");
	printf("ѧ�ţ�1512440234 ��������ԲԲ\n\n");
	printf("input the number of processes:");
	scanf("%d",&num);
	input();    
	RR();    
	output();
}    
