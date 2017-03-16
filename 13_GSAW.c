#include <stdio.h>
#include <process.h>
#include <math.h>
#include <time.h>
int seed;//随机数种子
int rr[10000][3000];//存储步数为n时第m次计算的位移平方到位置rr[n][m-1]
long double w[10000][3000];//存储粒子运动到位置rr[n][m-1]的几率权重到位置w[n][m-1]
#define size 250//表征粒子运动的空间范围
int randomz(int a,int b,int c)
{//返回0到b间的随机数，a为乘子，b为模数，c为上一个随机数的值
	int q,qq,r,rr,y;
	q=b/a;
	r=b-a*q;//r=(b mod a)
	qq=c/q;
	rr=c-q*qq;//rr=(c mod q)
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//新随机数
}
void GSAW(int n,int m)//n为GSAW的运动步数,m表明这是该运动步数的第m+1次计算
{
	int i;//循环变量
	int seedd;//表征粒子下一步随机行走的方向
	int point[2*size+1][2*size+1]={0};//初始化粒子运动的空间
	int c;//表征粒子新位置周围已经过的位置,当c=4时粒子将死亡
	int dx,dy;//为粒子每一步的位移
	int x=size,y=size;//为粒子的初始位置,在二维数组point[][]的中心
	point[size][size]=1;//粒子初始位置对应二维数组元素取1
	w[n][m]=1;//初始化权重
	for(i=1;i<n;i++)
	{
		c=point[x-1][y]+point[x][y+1]+point[x+1][y]+point[x][y-1];//计算c
		if(c==4)//粒子周围已全部走过
		{
			w[n][m]=0;//粒子死亡
			break;
		}
		while(0<x&&x<2*size&&0<y&&y<2*size)//控制粒子在空间内运动
		{
			dx=dy=0;//每一步位移初始化为0
			seed=randomz(16807,2147483647,seed);//迭代产生新随机数
			seedd=seed%4;//得到0,1,2,3均匀分布的随机数
			switch(seedd)
			{
			case 0: dx=-1; break;//左行一步
			case 1: dy=-1; break;//下行一步
			case 2: dx=1; break;//右行一步
			default: dy=1;//上行一步
			}
			if(point[x+dx][y+dy]==0)//欲前往的位置没有走过
			{
				c=point[x-1][y]+point[x][y+1]+point[x+1][y]+point[x][y-1];//计算c
				x+=dx;
				y+=dy;//走到新位置
				point[x][y]=1;//在空间中记录为已走过
				w[n][m]*=(long double)(4-c)/3;//计算当前的权重
				break;
			}
		}
	}
	rr[n][m]=(x-size)*(x-size)+(y-size)*(y-size);//计算当前的位移平方
}
void statistic()//整理GSAW得到的数据
{
	int i,m;//循环变量
	long double sumw,sumrr;//分别为对相同的步数n,计算的权重之和,以及计算的位移平方的权重和
	FILE *fx;//存储数据d文件的指针
	fx=fopen("GSAW.dat","w+");
	for(i=3;i<200;i+=1+i/10)//不同的步数
	{
		sumw=0;
		sumrr=0;
		for(m=0;m<100+10*i;m++)//统计当前步数行走100+10*i次的结果
		{
			GSAW(i,m);
			sumrr+=(long double)rr[i][m]*w[i][m];//计算sumrr
			sumw+=w[i][m];//计算sumw
		}
		if(sumw!=0&&sumrr!=0)//当前步数下有最终没有死亡的粒子
			fprintf(fx,"%10d%20.10f\n",i,sumrr/sumw);//输出步数和对应的位移平方均值到文件
	}
	fclose(fx);
}
void main()
{
	double duration;
	clock_t start,finish;//时间计数变量
	printf("input seed for the growing self-avoiding walking:    ");
	scanf("%d",&seed);
	start=clock();//计时点1
	statistic();//调用函数statistic()
	finish=clock();//计时点2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("You have been waiting for %.6f seconds\n",duration);//输出程序运行时间
	system("pause");
}