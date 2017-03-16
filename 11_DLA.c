#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
#define length 1000
#define width 1000
int point[2*length+1][2*width+1];//�ܵĿɹ������˶��ķ�Χ���ص�Ϊ2001*2001
int x[20000],y[20000];//�洢���۵��XY����
int n;//���۵�����
int a=10;//�߽�ֵ�������Ӳ���λ�������۵���������[-a,a]*[-a,a]�������α߽���
int randomz(int a,int b,int c)
{//����0��b����������aΪ���ӣ�bΪģ����cΪ��һ���������ֵ
	int q,qq,r,rr,y;
	q=b/a;
	r=b-a*q;//r=(b mod a);
	qq=c/q;
	rr=c-q*qq;//rr=(c mod q);
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//�������
}
void fractal(int n)//ģ��DLA�����ĺ���
{
	int i,j;//ѭ������
	int xx,yy;//Ϊÿ��������ߵ����ӵ�XY����
	int c,s;//�洢����16807�����������������ֵ
	int d;//���ڱ����˶��е�������Χ�Ƿ������۵�
	long double cc;//cc=c/2147483647
	int max=1;//�洢��ǰ�����۵ĵ������������ĵ����ƫ��ֵ
	FILE *fp;
	for(i=0;i<2*length+1;i++)
	{
		for(j=0;j<2*width+1;j++)
			point[i][j]=0;//��ʼ����ά����point[][]
	}
	point[length][width]=1;//���۵�����
	x[0]=length;
	y[0]=width;
	fp=fopen("fractal.dat","w+");//��dat�ļ�fractal�洢���۵�����
	printf("input seed for the random position    ");
	scanf("%d",&c);//��������ֵ�������ӵ��������
	printf("input seed for the random walking    ");
	scanf("%d",&s);//��������ֵ�������ӵ��������
	for(i=1;i<n;i++)
	{
		d=0;//��ʼ��
		cc=(long double)c/2147483647;
		switch(c%4){
		case 0: xx=a+length;                 yy=a-(int)(8*a*cc)+width;   break;//���ұ߽���
		case 1: xx=3*a-(int)(8*a*cc)+length; yy=-a+width;                break;//���±߽���
		case 2: xx=-a+length;                yy=5*a-(int)(8*a*cc)+width; break;//����߽���
		default: xx=7*a-(int)(8*a*cc)+length; yy=a+width;//���ϱ߽���
		}
		c=randomz(16807,2147483647,c);//�������
		while(d==0)//��Χ�����۵�
		{
			switch(s%4){//�������
			case 0: yy++; break;
			case 1: xx++; break;
			case 2: yy--; break;
			default: xx--;
			}
			s=randomz(16807,2147483647,s);//�������
			if(abs(xx-length)>1.2*a+10||abs(yy-width)>1.2*a+10)
			{//�˶��㳬��Ҫ��
				xx=yy=length;
				i--;
				break;
			}
			d=point[xx-1][yy]+point[xx+1][yy]+point[xx][yy-1]+point[xx][yy+1];
			if(d>0)//����
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
		a=(int)1.2*max+10;//�±߽�
	}
	printf("%d\n",i);
	for(i=0;i<n;i++)
		fprintf(fp,"%6d%6d\n",x[i],y[i]);//�������
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
							m++;//���۵㣬ͳ��ֵ+1
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
	clock_t start,finish;//ʱ���������
	double duration;//�洢��������ʱ��
	printf("input the number of the point    ");
	scanf("%d",&n);
	start=clock();//��ʱ��1
	fractal(n);
	finish=clock();//��ʱ��2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the programme has been running for %.6f seconds\n\a",duration);//�����������ʱ��
	measure1();
	measure2();
	system("pause");
}