#include <stdio.h>
#include <math.h>
#include <process.h>
#define pi 3.1415926535897932384626
#define e 2.71828182845904523536
long double gauss(long double x){//Gauss�ֲ����������غ���ֵ
	return exp(-0.5*x*x)/sqrt(2*pi);
}
long double trans_lorentz(long double x){//��ϵ��k=1.521���Lorentz�ֲ����������غ���ֵ
	return 1.521/pi/(1+x*x);
}
int self_random(int a,int b,int c){//����0��b����������aΪ���ӣ�bΪģ����cΪ��һ���������ֵ��
	int q,qq,r,rr,y;
	q=b/a;
	r=b-q*a;//r=(b mod a);
	qq=c/q;
	rr=c-qq*q;//rr=(c mod q);
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//�������
}
void main(){
	int i,j,n,m,c1,c2;//i,jΪ����������nΪȡ�������mΪ��ѡ���ĵ�����c1��c2Ϊ����������е�����
	int group[2000]={0};//���ڴ洢��ѡȡ����X������[-10,10]������0.01���������������
	long double u,v;//u,vΪ[0,1]�Ͼ��ȷֲ����������; 
	long double x,y;//xΪ��Lorentz�ֲ����ȡ����ֵ, yΪ(0,1.521/pi/(1+x*x))�ϵľ��ȷֲ����������
	FILE *fgroup;//*fgroup���ڴ洢��һ��������group[2000]��Ԫ��ֵ
	if((fgroup=fopen("group_gauss.dat","w+"))==NULL){
		printf("can not open the file\n");
		exit(0);
	}//�����ļ�"group_gauss.dat"���ڴ洢��һ����group[2000]��Ԫ��ֵ
	printf("input n    ");
	scanf("%d",&n);
	printf("input seed1   ");
	scanf("%d",&c1);
	printf("input seed2   ");
	scanf("%d",&c2);
	for(i=0,m=0;i<n;i++){//����n��ȡ��
		u=(long double)c1/2147483647;//�õ���uΪ��һ����������
		v=(long double)c2/2147483647;//�õ���vΪ��һ����������
		c1=self_random(16807,2147483647,c1);//�����������
		c2=self_random(16807,2147483647,c2);//�����������
		x=tan(pi*(u-0.5));//xΪ��Lorentz�ֲ����ȡ����ֵ
		y=trans_lorentz(x)*v;//yΪ(0,1.521/pi/(1+x*x))�ľ��ȷֲ����������
		if(y<gauss(x)){//����ȡ��Ҫ��
			m++;//��ѡ����ֵ��1
			if(x*x<=100){//ͳ��[-10,10]�ڵ�x��������ֲ�
				j=(int)100*(10+x);//����0.01������ͳ��
				group[j]++;//��Ӧ����ͳ��ֵ+1
			}
		}
	}
	printf("����Ч��Ϊ  %.9f\n",(long double)m/n);
	for(i=m,j=0;j<2000;j++){
		fprintf(fgroup,"%18.16f\n",(long double)group[j]/m);//�����һ���������group[2000]Ԫ��ֵ���ļ�
		i-=group[j];
	}
	if(i==0)
		printf("the worry about the data-overflow is unnecessary\n");
	fclose(fgroup);//�ر��ļ�
	system("pause");
}