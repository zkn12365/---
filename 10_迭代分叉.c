#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
#define pi 3.14159265358979323846264
void main()
{
	int i,j;//i,jΪѭ������
	int m,n;//mΪ��������,nΪϵ��lambda��ȡֵ����
	long double x,xx;//xxΪx�ĳ�ʼֵ,xΪÿ�ε����Ľ��,�ڵ����и���
	long double y;//���ڴ洢��ͬ��lambdaֵ,��ѭ���и���
	long double a,b;//ϵ��lambdaȡֵ����Ϊ[a,b]
	clock_t start,finish;//ʱ���������
	double duration;//�洢��������ʱ��
	FILE *fx;//�ļ�ָ��,��Ӧ�洢����xֵ�������ļ�
	if((fx=fopen("fencha.dat","w+"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
	}//���ļ�
	printf("����x�ĳ�ʼֵ    ");
	scanf("%lf",&xx);//����x�ĳ�ʼֵ
	printf("�����������    ");
	scanf("%d",&m);//�����������
	printf("����lambda���Ͻ�    ");
	scanf("%lf",&b);//����lambda���Ͻ�
	printf("����lambda���½�    ");
	scanf("%lf",&a);//����lambda���½�
	printf("����lambdaȡ����    ");
	scanf("%d",&n);//����lambda��ȡ�����
	start=clock();//��ʱ��1
	for(j=0;j<n;j++)
	{
		x=xx;//�Բ�ͬ��lambda,��ʼ��x
		y=a+(b-a)/(long double)n*j;//lambda�ĵ�j+1��ȡֵ���ֵ
		for(i=0;i<100;i++)
			x=y*sin(pi*x);//���е���100��,ʹʵ��ȡ��xֵ��Ӧ��ʼֵ��ͬ
		for(i=0;i<m;i++)
		{
			x=y*sin(pi*x);
			fprintf(fx,"%.8f\n",x);//����x,������ļ�
		}
	}
	fclose(fx);//�ر��ļ�
	finish=clock();//��ʱ��2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the programme has been running for %.6f seconds\n",duration);//�����������ʱ��
	system("pause");
}