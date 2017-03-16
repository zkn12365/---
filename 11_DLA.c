#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
#define length 1000
#define width 1000
int point[2*length+1][2*width+1];//总的可供粒子运动的范围像素点为2001*2001
int x[20000],y[20000];//存储凝聚点的XY坐标
int n;//凝聚点总数
int a=10;//边界值，即粒子产生位置在凝聚点种子四周[-a,a]*[-a,a]的正方形边界上
int randomz(int a,int b,int c)
{//返回0到b间的随机数，a为乘子，b为模数，c为上一个随机数的值
	int q,qq,r,rr,y;
	q=b/a;
	r=b-a*q;//r=(b mod a);
	qq=c/q;
	rr=c-q*qq;//rr=(c mod q);
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//新随机数
}
void fractal(int n)//模拟DLA生长的函数
{
	int i,j;//循环变量
	int xx,yy;//为每次随机行走的粒子的XY坐标
	int c,s;//存储两个16807随机数产生器的种子值
	int d;//用于表征运动中的粒子周围是否有凝聚点
	long double cc;//cc=c/2147483647
	int max=1;//存储当前已凝聚的点的坐标相对中心的最大偏移值
	FILE *fp;
	for(i=0;i<2*length+1;i++)
	{
		for(j=0;j<2*width+1;j++)
			point[i][j]=0;//初始化二维数组point[][]
	}
	point[length][width]=1;//凝聚点种子
	x[0]=length;
	y[0]=width;
	fp=fopen("fractal.dat","w+");//打开dat文件fractal存储凝聚点坐标
	printf("input seed for the random position    ");
	scanf("%d",&c);//键入种子值用于粒子的随机产生
	printf("input seed for the random walking    ");
	scanf("%d",&s);//键入种子值用于粒子的随机行走
	for(i=1;i<n;i++)
	{
		d=0;//初始化
		cc=(long double)c/2147483647;
		switch(c%4){
		case 0: xx=a+length;                 yy=a-(int)(8*a*cc)+width;   break;//在右边界上
		case 1: xx=3*a-(int)(8*a*cc)+length; yy=-a+width;                break;//在下边界上
		case 2: xx=-a+length;                yy=5*a-(int)(8*a*cc)+width; break;//在左边界上
		default: xx=7*a-(int)(8*a*cc)+length; yy=a+width;//在上边界上
		}
		c=randomz(16807,2147483647,c);//新随机数
		while(d==0)//周围无凝聚点
		{
			switch(s%4){//随机行走
			case 0: yy++; break;
			case 1: xx++; break;
			case 2: yy--; break;
			default: xx--;
			}
			s=randomz(16807,2147483647,s);//新随机数
			if(abs(xx-length)>1.2*a+10||abs(yy-width)>1.2*a+10)
			{//运动点超出要求
				xx=yy=length;
				i--;
				break;
			}
			d=point[xx-1][yy]+point[xx+1][yy]+point[xx][yy-1]+point[xx][yy+1];
			if(d>0)//凝聚
			{
				point[xx][yy]=1;
				x[i]=xx;
				y[i]=yy;
				break;
			}
		}
		if(abs(xx-length)>max)
			max=abs(xx-length);
		if(abs(yy-width)>max)
			max=abs(yy-width);
		a=(int)1.2*max+10;//新边界
	}
	printf("%d\n",i);
	for(i=0;i<n;i++)
		fprintf(fp,"%6d%6d\n",x[i],y[i]);//输出数据
	fclose(fp);
}
void measure1()
{
	int i,j,k,l,p;
	int xx,yy;
	double m,w;
	FILE *fp;
	fp=fopen("DLA1.dat","w+");
	for(i=2;i<9;i++)
	{
		m=0;
		for(j=0;j<pow(2,i);j++)
		{
			for(k=0;k<pow(2,i);k++)
			{
				for(l=0;l<2*a/pow(2,i);l++)
				{
					w=m;
					for(p=0;p<2*a/pow(2,i);p++)
					{
						xx=(int)(j*2*a/pow(2,i)-a+length+l);
					    yy=(int)(k*2*a/pow(2,i)-a+width+p);
				    	if(point[xx][yy]!=0)
						{
							m++;//凝聚点，统计值+1
							break;
						}
					}
					if(w!=m)
						break;
				}
			}
		}
		fprintf(fp,"%6d%15.9f\n",i,m);
	}
	fclose(fp);
}
void measure2()
{
	int i,j,k;
	double w=a;
	int m;
	FILE *fp;
	fp=fopen("DLA2.dat","w+");
	for(i=0;i<7;i++)
	{
		w*=0.5;
		m=0;
		for(k=length-w;k<length+w;k++)
		{
			for(j=width-w;j<width+w;j++)
			{
				if(point[k][j]==1)
					m++;
			}
		}
		fprintf(fp,"%15.9f%6d\n",2*w,m);
	}
	fclose(fp);
}
void main()
{
	clock_t start,finish;//时间计数变量
	double duration;//存储程序运行时间
	printf("input the number of the point    ");
	scanf("%d",&n);
	start=clock();//计时点1
	fractal(n);
	finish=clock();//计时点2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the programme has been running for %.6f seconds\n\a",duration);//输出程序运行时间
	measure1();
	measure2();
	system("pause");
}