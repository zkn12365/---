#include <stdio.h>
#include <math.h>
#include <process.h>
#include <time.h>
#define pi 3.14159265358979323846264
int randomz(int a,int b,int c)
{//16807�����������
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
{//����theta��������ߣ�theta Ϊ��ʼλ�ã�dtheta Ϊ������n Ϊ���ߴ�����s Ϊ����������������������
	int i,y;//iΪ����������yΪ���ߺ���Գ�ʼλ�õ�ƫ�Ʋ���
	for(y=0,i=0;i<n;i++)
	{
		if(s<1073741824) y-=1;//��ƫһ��
		else y+=1;//��ƫһ��
		s=randomz(16807,2147483647,s);//�������
	}
	return theta+(double)y*dtheta;//����n���������λ��
}
void main()
{
	int i,j,k;//��������
	int m;//���Ӹ���
	int n[20];//�洢��ͬ�����߲���
	int c;//����������
	double Ct[20];//�洢��ͬ������Ӧ�������ϵ��
	double theta1,theta2,dtheta=pi/10;//theta1Ϊ��ʼ���꣬theta2Ϊ���ߺ����꣬dthetaΪ����
	clock_t start,finish;//ʱ����������ڼ����������ʱ��
	double duration;//���ڼ����������ʱ��
	FILE *fx;//�ļ�ָ�����ڴ洢������߲�������Ӧ����غ���
	if((fx=fopen("rw of particles with random orientation.dat","w+"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
	}//���ļ�
	printf("���뼫��������    ");
	scanf("%d",&c);//�����������ļ�����ֲ����������
	printf("�������Ӹ���    ");
	scanf("%d",&m);//�����������ļ�����ֲ����������

	for(k=0;k<10;k++)
	{
		printf("�����%d�����߲���  ",k+1);
		scanf("%d",&n[k]);//�������߲���
		printf("����������߲�������������0����������-1\n");
		scanf("%d",&j);
		if(j==0) break;//�˳����벽����ѭ��
	}
	start=clock();//��ʱ���������п�ʼ
	for(j=0;j<k+1;j++)
	{//jѭ���в�ͬ�����߲���ֵ
		for(Ct[j]=i=0;i<m;i++)
		{//iѭ������m����ͬ������
			c=randomz(16807,2147483647,c);//�������
			theta1=(double)c*2*pi/2147483647;//[0,2pi]�Ͼ��ȷֲ����������������theta1
			theta2=rw(theta1,dtheta,n[j],pow((i+1),2)*(j+1));//rw�����������ߺ��λ�����꣬����theta2
			Ct[j]+=cos(theta1)*cos(theta2);//��������غ���
		}
		Ct[j]/=m;//��������غ���
		fprintf(fx,"%d    %.8f\n",n[j],Ct[j]);//������߲�������Ӧ����غ���ֵ���ļ�
	}
	fclose(fx);
	finish=clock();//��ʱ���������н���
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the program has been running for %.6f seconds\n",duration);//�������ʱ�䵽��Ļ
	system("pause");
}
