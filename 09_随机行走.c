#include <stdio.h>
#include <math.h>
#include <process.h>
#include <time.h>
#define pi 3.14159265358979323846264
int randomz(int a,int b,int c)
{//16807随机数产生器
	int q,qq,r,rr,y;
	q=b/a;
	r=b-a*q;
	qq=c/q;
	rr=c-qq*q;
	y=a*rr-r*qq;
	if(y<0) y+=b;
	return y;
}
double rw(double theta,double dtheta,int n,int s)
{//坐标theta的随机行走，theta 为初始位置，dtheta 为步长，n 为行走次数，s 为随机行走所用随机数的种子
	int i,y;//i为计数变量，y为行走后相对初始位置的偏移步数
	for(y=0,i=0;i<n;i++)
	{
		if(s<1073741824) y-=1;//右偏一步
		else y+=1;//左偏一步
		s=randomz(16807,2147483647,s);//新随机数
	}
	return theta+(double)y*dtheta;//返回n步后的坐标位置
}
void main()
{
	int i,j,k;//计数变量
	int m;//粒子个数
	int n[20];//存储不同的行走步数
	int c;//极坐标种子
	double Ct[20];//存储不同步数对应的自相关系数
	double theta1,theta2,dtheta=pi/10;//theta1为初始坐标，theta2为行走后坐标，dtheta为步长
	clock_t start,finish;//时间变量，用于计算程序运行时间
	double duration;//用于计算程序运行时间
	FILE *fx;//文件指针用于存储随机行走步数及对应自相关函数
	if((fx=fopen("rw of particles with random orientation.dat","w+"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
	}//打开文件
	printf("输入极坐标种子    ");
	scanf("%d",&c);//键入产生随机的极坐标分布所需的种子
	printf("输入粒子个数    ");
	scanf("%d",&m);//键入产生随机的极坐标分布所需的种子

	for(k=0;k<10;k++)
	{
		printf("输入第%d个行走步数  ",k+1);
		scanf("%d",&n[k]);//键入行走步数
		printf("如果输入行走步数结束，输入0；否则输入-1\n");
		scanf("%d",&j);
		if(j==0) break;//退出输入步数的循环
	}
	start=clock();//计时，程序运行开始
	for(j=0;j<k+1;j++)
	{//j循环有不同的行走步数值
		for(Ct[j]=i=0;i<m;i++)
		{//i循环考虑m个不同的粒子
			c=randomz(16807,2147483647,c);//新随机数
			theta1=(double)c*2*pi/2147483647;//[0,2pi]上均匀分布的随机抽样，赋给theta1
			theta2=rw(theta1,dtheta,n[j],pow((i+1),2)*(j+1));//rw函数计算行走后的位置坐标，赋给theta2
			Ct[j]+=cos(theta1)*cos(theta2);//计算自相关函数
		}
		Ct[j]/=m;//计算自相关函数
		fprintf(fx,"%d    %.8f\n",n[j],Ct[j]);//输出行走步数及对应自相关函数值到文件
	}
	fclose(fx);
	finish=clock();//计时，程序运行结束
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the program has been running for %.6f seconds\n",duration);//输出运行时间到屏幕
	system("pause");
}
