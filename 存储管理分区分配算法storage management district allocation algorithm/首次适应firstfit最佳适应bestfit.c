#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 32767

/********************分区描述区****************/
typedef struct node   
{
	int address,size;
	struct node *next;
}MEMORY;

MEMORY *assignment(MEMORY *head,int application);
void best(MEMORY *head,MEMORY *back1);
void first(MEMORY *head,MEMORY *back1) ;
int backcheck(MEMORY *head,MEMORY *back1);
void print(MEMORY *head);
int block,application1;
char way[20];
MEMORY *head,*back,*assign1,*p;

/*******************建立链表显示信息*****************/
void headline()
{ 
	head=(MEMORY*)malloc(sizeof(MEMORY)); 
	p=(MEMORY*)malloc(sizeof(MEMORY));
	head->size=MAX;
	head->address=0;
	head->next=p;
	block=1;
	p->size=MAX;
	p->address=0;
	p->next=NULL;
	printf("【存储区管理分区分配算法演示】\n");
	printf("学号：1512440234 姓名：侯圆圆\n\n");
	print(head);  
	printf("\n");
}

/*****************分配空间*******************/
MEMORY *assignment(MEMORY *head,int application)
{
	MEMORY *after,*before,*assign;
	assign=(MEMORY*)malloc(sizeof(MEMORY));
	assign->size=application;
	assign->next=NULL;
	if(application>head->size||application<=0)
		assign->address=-1; 
	else
	{
		before=head;
		after=head->next;
		while(after->size<application)
		{
			before=before->next;
			after=after->next;
		}
		if(after->size==application)
		{
			if(after->size==head->size)
				block--;
			before->next=after->next;
			assign->address=after->address;
			free(after);
		}
		else
		{
			if(after->size==head->size) block--;
			after->size=after->size-application; 
			assign->address=after->address+after->size;
			if(way=="best")
			{
				before->next=after->next;
				back=after;
				first(head,back);
			}
		}
		if(block==0) 
		{
			before=head;
			head->size=0;
			block=1;
			while(before!=NULL)
			{
				if(before->size>head->size)
				{
					head->size=before->size;
					block=1;
				}
				else
					if(before->size==head->size)
						block++;
				before=before->next;
			}
		}
	}
	assign1=assign;
	return assign1; 
}

/********************首次适应算法****************/
void first(MEMORY *head,MEMORY *back1)
{
	MEMORY *before,*after;
	int insert;
	before=head;
	after=head->next;
	insert=0;
	while(!insert) //将回收区插入空闲区
	{
		if((after==NULL)||
			((back1->address<=after->address)&&
			(back1->address>=before->address)))
		{
			before->next=back1;
			back1->next=after;
			insert=1;
		}
		else
		{
			before=before->next;
			after=after->next;
		}
	}
	if(back1->address==before->address+before->size)
	{
		before->size=before->size+back1->size;
		before->next=back1->next;
		free(back1);
		back1=before;
	}
	if(after!=NULL&&(after->address==back1->address+back1->size))
	{  
		back1->size=back1->size+after->size;
		back1->next=after->next;
		free(after);
	}
	if(head->size<back1->size)
	{
		head->size=back1->size;
		block=1;
	}
	else
		if(head->size==back1->size)
			block++;
}

/*******************最佳适应算法*****************/
void best(MEMORY *head,MEMORY *back1)
{
	MEMORY *before,*after;
	int insert ;
	insert=0;
	before=head;
	after=head->next;
	if(head->next==NULL) 
	{
		head->size=back1->size;
		head->next=back1;
		block++;
		back1->next=NULL;
	}
	else
	{
		while(after!=NULL) 
			if(back1->address==after->size+after->address)
			{
				before->next=after->next;
				back->size=after->size+back1->size;
				free(after);
				after=NULL;
			}
			else
			{
				after=after->next;
				before=before->next;
			}
			before=head;
			after=head->next;
			while(after!=NULL)
				if(after->address==back1->size+back1->address) 
				{
					back1->size=back1->size+after->size;
					before->next=after->next;
					free(after);
					after=NULL;
				}
				else
				{
					before=before->next;
					after=after->next;
				}
				before=head;
				after=head->next;
				do{
					if(after==NULL||(after->size>back1->size))
					{
						before->next=back1;
						back1->next=after;
						insert=1;
					}
					else
					{
						before=before->next;
						after=after->next;
					}
				}while(!insert);
				if(head->size<back1->size) 
				{
					head->size=back1->size;
					block++;
				}
				else
					if(head->size==back1->size)
						block++;
	}
}

/*******************输出分配状态链表*****************/
void print(MEMORY *head) 
{
	MEMORY *before;
	int index;
	before=head->next;
	index=1;
	if(head->next==NULL)
		printf("NO part for assignment!!\n");
	else
	{
		printf("   Index   *   address    *     end    *     size     \n");
		while(before!=NULL)
		{
			printf("     %-13d%-13d%-13d%-13d\n",index,before->address,before->address+before->size-1,before->size);
			index++;
			before=before->next;		 
		}
	}
}

/*******************检查回收块合法性*****************/
int backcheck(MEMORY *head,MEMORY *back1)
{
	MEMORY *before;
	int check=1;
	if(back1->address<0||back1->size<0)
		check=0;
	before=head->next;
	while((before!=NULL)&&check)
		if(((back1->address<before->address)
			&&(back1->address+back1->size>before->address))
			||((back1->address>=before->address)
			&&(back1->address<before->address+before->size)))
			check=0;
		else
			before=before->next;
	if(check==0)
		printf("Error input!!\n");
	return check;  
}

/***************主函数*****************/
main()
{  
	int check;
	char choose[5];
	headline();
	printf("input the way(best or first):");
	scanf("%s",&way);
	do{
		printf("Assign or Accept(as or ac):");
		scanf("%s",choose); 
		if(strcmp(choose,"as")==0) 
		{
			printf("input APPLICATION:");
			scanf("%d",&application1);
			assign1=assignment(head,application1);
			if(assign1->address==-1)
				printf("Too large application!\n\n");
			else
				printf("SUCCESS!!!  ADDRESS=%5d\n\n",assign1->address); 
			print(head); 
		}
		else
			if(strcmp(choose,"ac")==0) 
			{
				back=(MEMORY*)malloc(sizeof(MEMORY));
				printf("Input adr and size:");
				scanf("%d%d",&back->address,&back->size);
				printf("\n");
				check=backcheck(head,back); 
				if(check==1)
				{
					if(way=="first")
						first(head,back); 
					else
						best(head,back);
					print(head);

				}
			}
	}while(!strcmp(choose,"as")||!strcmp(choose,"ac"));
}