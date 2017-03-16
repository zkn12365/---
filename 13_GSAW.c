#include <stdio.h>
#include <process.h>
#include <math.h>
#include <time.h>
int seed;//���������
int rr[10000][3000];//�洢����Ϊnʱ��m�μ����λ��ƽ����λ��rr[n][m-1]
long double w[10000][3000];//�洢�����˶���λ��rr[n][m-1]�ļ���Ȩ�ص�λ��w[n][m-1]
#define size 250//���������˶��Ŀռ䷶Χ
int randomz(int a,int b,int c)
{//����0��b����������aΪ���ӣ�bΪģ����cΪ��һ���������ֵ
	int q,qq,r,rr,y;
	q=b/a;
	r=b-a*q;//r=(b mod a)
	qq=c/q;
	rr=c-q*qq;//rr=(c mod q)
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//�������
}
void GSAW(int n,int m)//nΪGSAW���˶�����,m�������Ǹ��˶������ĵ�m+1�μ���
{
	int i;//ѭ������
	int seedd;//����������һ��������ߵķ���
	int point[2*size+1][2*size+1]={0};//��ʼ�������˶��Ŀռ�
	int c;//����������λ����Χ�Ѿ�����λ��,��c=4ʱ���ӽ�����
	int dx,dy;//Ϊ����ÿһ����λ��
	int x=size,y=size;//Ϊ���ӵĳ�ʼλ��,�ڶ�ά����point[][]������
	point[size][size]=1;//���ӳ�ʼλ�ö�Ӧ��ά����Ԫ��ȡ1
	w[n][m]=1;//��ʼ��Ȩ��
	for(i=1;i<n;i++)
	{
		c=point[x-1][y]+point[x][y+1]+point[x+1][y]+point[x][y-1];//����c
		if(c==4)//������Χ��ȫ���߹�
		{
			w[n][m]=0;//��������
			break;
		}
		while(0<x&&x<2*size&&0<y&&y<2*size)//���������ڿռ����˶�
		{
			dx=dy=0;//ÿһ��λ�Ƴ�ʼ��Ϊ0
			seed=randomz(16807,2147483647,seed);//���������������
			seedd=seed%4;//�õ�0,1,2,3���ȷֲ��������
			switch(seedd)
			{
			case 0: dx=-1; break;//����һ��
			case 1: dy=-1; break;//����һ��
			case 2: dx=1; break;//����һ��
			default: dy=1;//����һ��
			}
			if(point[x+dx][y+dy]==0)//��ǰ����λ��û���߹�
			{
				c=point[x-1][y]+point[x][y+1]+point[x+1][y]+point[x][y-1];//����c
				x+=dx;
				y+=dy;//�ߵ���λ��
				point[x][y]=1;//�ڿռ��м�¼Ϊ���߹�
				w[n][m]*=(long double)(4-c)/3;//���㵱ǰ��Ȩ��
				break;
			}
		}
	}
	rr[n][m]=(x-size)*(x-size)+(y-size)*(y-size);//���㵱ǰ��λ��ƽ��
}
void statistic()//����GSAW�õ�������
{
	int i,m;//ѭ������
	long double sumw,sumrr;//�ֱ�Ϊ����ͬ�Ĳ���n,�����Ȩ��֮��,�Լ������λ��ƽ����Ȩ�غ�
	FILE *fx;//�洢����d�ļ���ָ��
	fx=fopen("GSAW.dat","w+");
	for(i=3;i<200;i+=1+i/10)//��ͬ�Ĳ���
	{
		sumw=0;
		sumrr=0;
		for(m=0;m<100+10*i;m++)//ͳ�Ƶ�ǰ��������100+10*i�εĽ��
		{
			GSAW(i,m);
			sumrr+=(long double)rr[i][m]*w[i][m];//����sumrr
			sumw+=w[i][m];//����sumw
		}
		if(sumw!=0&&sumrr!=0)//��ǰ������������û������������
			fprintf(fx,"%10d%20.10f\n",i,sumrr/sumw);//��������Ͷ�Ӧ��λ��ƽ����ֵ���ļ�
	}
	fclose(fx);
}
void main()
{
	double duration;
	clock_t start,finish;//ʱ���������
	printf("input seed for the growing self-avoiding walking:    ");
	scanf("%d",&seed);
	start=clock();//��ʱ��1
	statistic();//���ú���statistic()
	finish=clock();//��ʱ��2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("You have been waiting for %.6f seconds\n",duration);//�����������ʱ��
	system("pause");
}