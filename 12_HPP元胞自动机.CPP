#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
#define a 101
#define R 50
int point[4*a+1][4*a+1];//总的可供粒子运动的范围为805*805,(i,j)位置元素取0代表无粒子,取1代表有粒子,取3代表为墙,具体见后文
FILE *fp,*fpxy;
int randomz(int multiply,int b,int c)
{//返回0到b间的随机数，a为乘子，b为模数，c为上一个随机数的值
	int q,qq,r,rr,y;
	q=b/multiply;
	r=b-multiply*q;//r=(b mod a);
	qq=c/q;
	rr=c-q*qq;//rr=(c mod q);
	y=multiply*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//新随机数
}
void move(int i,int j)//将(i,j)位置周围4个粒子看作一个元胞，使元胞按规则演化一步的函数
{
	int c,d;
	c=1000*point[i-1][j]+100*point[i][j+1]+10*point[i+1][j]+point[i][j-1];//通过c的不同值表征中心点上下左右4个位置的状态
	if(c==1010)//中心上下位置有粒子将要进行对心碰撞
	{
		point[i][j+1]=point[i][j-1]=1;
		point[i-1][j]=point[i+1][j]=0;
	}//粒子偏离90°离开
	else if(c==101)//中心左右位置有粒子将要进行对心碰撞
	{
		point[i][j+1]=point[i][j-1]=0;
		point[i-1][j]=point[i+1][j]=1;
	}//粒子偏离90°离开
	else
	{//中心周围4个粒子中位于对称位置的两个位置交换状态，即若旧位置存在粒子，则沿原先方向运动1步，为2像素点
		d=point[i][j+1];
		point[i][j+1]=point[i][j-1];
		point[i][j-1]=d;
		d=point[i+1][j];
		point[i+1][j]=point[i-1][j];
		point[i-1][j]=d;
	}
}
void set()//设定空间的初始状态，包括起“墙”作用的不动的边界和粒子的初始状态
{
	int i,j;//循环变量
	int m=0;//用于统计粒子个数
	int seed,seedd;//seed为随机数，seedd为seed变换到[0,4)后的离散值
	printf("input seed for the random walking:    ");
	scanf("%d",&seed);//键入随机数的种子
	for(i=0;i<4*a+1;i++)//初始化四周的边界,元素值为3
	{
		point[i][0]=3;
		point[0][i]=3;
		point[i][4*a]=3;
		point[4*a][i]=3;
	}
	for(i=1;i<4*a;i++)
		for(j=1;j<4*a;j++)//i,j的for循环遍历四周边界内的空间,均初始化为0
			point[i][j]=0;
	for(i=2-2*a;i<2*a;i+=2)
	{
		for(j=2-2*a;j<2*a;j+=2)//i,j的for循环遍历空间的像素点位置
		{
			if(i*i+j*j<=(R+3)*(R+3))//在圆形墙的外边界内
			{
				if(i*i+j*j<R*R)//在圆形墙的内边界内
				{
					if(abs(i)%4==2&&abs(j)%4==2)//为初始的粒子位置
					{
						seedd=(int)(((double)seed/2147483647)*4);
						switch(seedd)//粒子做4个方向，步长为1像素点的随机行走。由于粒子初始位置的设定，粒子间的距离范数仍为偶数，且无相撞
						{
				     	case 0: point[i+2*a][j+2*a+1]=1; break;
						case 1: point[i+2*a+1][j+2*a]=1; break;
						case 2: point[i+2*a][j+2*a-1]=1; break;
						default: point[i+2*a-1][j+2*a]=1;
						}
						seed=randomz(16807,2147483647,seed);//新随机数
						m++;//粒子数统计值+1
					}
					else point[i+2*a][j+2*a]=0;
				}
				else if(i>0&&abs(i-j)<10)//对应墙上开口的位置
					point[i+2*a][j+2*a]=0;
				else point[i+2*a][j+2*a]=3;//初始化为墙
			}
		}
	}
	printf("we got %d particles.\n",m);//输出粒子数
}
void HPP(int n)//使所有粒子按规则演化n步的函数
{
	int time,i,j;//循环变量
	for(time=0;time<n;time++)
	{//对不同的时间,元胞的中心点位置不同,取值可按time%2=0/1区分,对每一时刻的元胞中心点,默认周围粒子(上下左右共4个)速度方向指向中心点
		if(time%2==0)
		{
			for(i=2;i<4*a-1;i+=2)
				for(j=2+i%4;j<4*a-1;j+=4)
					if(point[i][j]!=3) move(i,j);//元胞不是边界,可演化
		}
		else
		{
			for(i=2;i<4*a-1;i+=2)
				for(j=4-i%4;j<4*a-1;j+=4)
					if(point[i][j]!=3) move(i,j);//元胞不是边界,可演化
		}
		for(i=0;i<4*a+1;i++)
	    	for(j=0;j<4*a+1;j++)
				if(point[i][j]==1)
					fprintf(fpxy,"%d    %d\n",i,j);//输出每一时刻粒子的XY坐标到文件
	}

}
void main()
{
	int i,j;
	int time;
	double duration;
	clock_t start,finish;//时间计数变量
	fp=fopen("HPP.dat","w+");//用于存储二维数组演化结果
	fpxy=fopen("HPPxy.dat","w+");//用于存储每一次演化后粒子的XY坐标
	printf("input an odd number for the time of walking:    ");
	scanf("%d",&time);//键入系统演化时间(每单位时间演化一次)
	start=clock();//计时点1
	set();//初始化系统状态
	HPP(time);//系统演化time次
	HPP(time);//系统演化time次
	for(i=0;i<4*a+1;i++)
		for(j=0;j<4*a+1;j++)
			fprintf(fp,"%d\n",point[i][j]);//输出最终的系统状态到文件
	fclose(fp);
	fclose(fpxy);
	finish=clock();//计时点2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("You have been waiting for %.6f seconds\n",duration);//输出程序运行时间
	system("pause");
}

