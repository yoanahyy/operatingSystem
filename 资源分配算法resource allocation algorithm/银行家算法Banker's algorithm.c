#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

int max[10][10];//进程最大资源需求量        
int allocation[10][10];//进程已分配的资源数
int need[10][10]; //利用两个数组计算出need矩阵
int available[10];
int request[10][10];
char *finish[10];
int safe[10];
int n,i,m;
int k=0;
int j=0;
int work[10];
int works[10][10];
void request1();
int b,h=1;
int f,e;

/*******************抬头信息显示******************/
void start()   
{
	printf("【银行家算法演示】\n");
	printf("学号：1512440234 姓名：侯圆圆\n\n");

}

/*******************退出信息显示******************/
void end()    
{
	system("cls");
	printf("\n\n       谢谢使用 \n");
}

/*******************录入进程资源数目******************/
void input()  
{   
	printf("Input the type of resource and number of customer:\n");
	scanf("%d%d",&f,&e);
	printf("Input the amount of resource(maximun)of each customer:\n");
	for(n=0;n<e;n++)
		for(m=0;m<f;m++)
			scanf("%d",&max[n][m]);   
	printf("Input the amount of resource(allocated)of each customer:\n");
	for(n=0;n<e;n++)
		for(m=0;m<f;m++)
			scanf("%d",&allocation[n][m]);  
	for(n=0;n<e;n++)
		for(m=0;m<f;m++)
			need[n][m]=max[n][m]-allocation[n][m];
	printf("Input available resource\n");
	for(m=0;m<f;m++)
		scanf("%d",&available[m]);   


}

/*******************输出系统现有资源情况******************/
void output()  
{
	printf("\n");
	printf("资源情况    Max     Allocation    Need      Available\n");
	printf("进程      A  B  C    A  B  C     A  B  C     A  B  C\n");

	for(n=0;n<e;n++)
	{
		printf("P%d%9d%3d%3d%5d%3d%3d%6d%3d%3d",n,max[n][0],max[n][1],max[n][2],allocation[n][0],allocation[n][1],allocation[n][2],need[n][0],need[n][1],need[n][2]);
		if (n==0)
			printf("%6d%3d%3d\n",available[0],available[1],available[2]);
		else
			printf("\n");
	}

}

/*******************Request[i,j]<=Available[j]时******************/
void change()  
{
	for (m=0;m<f;m++)
	{
		available[m]-=request[i][m];
		allocation[i][m]+=request[i][m];
		need[i][m]-=request[i][m];
	}
}

/*******************输出安全序列的资源情况******************/
void outputsafe()   
{
	printf("\n");
	printf("资源情况   Work       Need    Allocation Work+Allocation  Finish\n");
	printf("进程      A  B  C    A  B  C    A  B  C     A  B  C\n");
	for(n=0;n<e;n++)
		printf("P%d%9d%3d%3d%5d%3d%3d%5d%3d%3d%6d%3d%3d%12s\n",safe[n],works[safe[n]][0],works[safe[n]][1],works[safe[n]][2],need[safe[n]][0],need[safe[n]][1],need[safe[n]][2],allocation[safe[n]][0],allocation[safe[n]][1],allocation[safe[n]][2],works[safe[n]][0]+allocation[safe[n]][0],works[safe[n]][1]+allocation[safe[n]][1],works[safe[n]][2]+allocation[safe[n]][2],finish[n]);
	printf("\n");
}

/*******************安全性算法******************/
int check()    
{

	for (m=0;m<f;m++)   
		work[m]=available[m];
	for (n=0;n<e;n++)
	{
		finish[n]="false";
		safe[n]=0;
	}
	k=0;
	for (m=0;m<e;m++)
		for (n=0;n<e;n++)
			if(strcmp(finish[n],"false")==0 && need[n][0]<=work[0] && need[n][1]<=work[1] && need[n][2]<=work[2])   
			{
				safe[k]=n;  
				works[safe[k]][0]=work[0];
				works[safe[k]][1]=work[1];
				works[safe[k]][2]=work[2];
				work[0]+=allocation[n][0];   
				work[1]+=allocation[n][1];
				work[2]+=allocation[n][2];
				finish[n]="ture"; 
				k++;
			}
			for (m=0;m<5;m++) 
			{
				if (strcmp(finish[m],"false")==0)
				{  printf("\n");
				printf("System insecurity!!\n");
				return 0;    
				}
				else 
					if (m==4)     
					{   
						j=1;
						outputsafe();    
						printf("System security!\n");
						printf("Customer p%d can get resource immediately\n",i);
						printf("\n");
					}
			}
			return 1;
}


void request1()
{
	if (check()==0)     //找不到安全序列
	{
		exit(0);
	}
	for(;j==1;)     
	{
		printf("please input the customer name i(0、1、2、3、4)：");  
		scanf("%d",&i);
		printf("please input the customer P%d request%d：",i,i);
		for(n=0;n<f;n++)
			scanf("%d",&request[i][n]);
		for (;request[i][0]>need[i][0] || request[i][1]>need[i][1] || request[i][2]>need[i][2];)
		{
			printf("数据输入有误，请重试！\n请输入进程P%d的请求向量Request%d：",i,i);
			for(n=0;n<f;n++)
				scanf("%d",&request[i][n]);
		}
		if(request[i][0]<=available[0] && request[i][1]<=available[1] && request[i][2]<=available[2])  
		{	change();    
		j=0;
		}
		else
			printf("\nResource insufficient!!\nCustomer p%d can not obtain resource immediately\n",i);
		if (j==0)   //有足够资源分配
		{
			if(check()==0)    //分配无效
			{
				printf("Customer p%d can not obtain resource immediately\n",i);
				for (m=0;m<f;m++)    //恢复
				{
					available[m]+=request[i][m];
					allocation[i][m]-=request[i][m];
					need[i][m]+=request[i][m];
				}			

			}
		}
		printf("其他进程继续请求资源？(是：输入1  否：输入0)\n请输入：");
		scanf("%d",&j);     
		printf("\n");
	}
}

/*******************主函数******************/
void main()  
{
	start();
	input();	
	while(h){
		system("cls"); 
		{printf("1.judge the system security\n");
		printf("2.judge the request security\n");
		printf("3.quit\n");
		printf("\nplease choose:");
		scanf("%d",&b);}
		switch(b)
		{
		case 1:  check();   break;
		case 2:  request1();   break;
		case 3:h=0; end();      break;
		}
		printf("\n");
		system("pause");
	}
}