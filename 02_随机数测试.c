#include <stdio.h>
#include <process.h>
#include <math.h>
int self_random(int a,int b,int c) {//����0��b֮����������aΪ����,bΪģ��,cΪ�ϸ��������ֵ;
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

long double homo(int a,int b,int c,int n){//������Ķ����Լ��飨����C(l)ϵ����
	int i,x;
	long double yy,xx,px=0,py=0,pxx=0,pxy=0,cl;
		for (i=0;i<n;i++){
		x=c;
		c=self_random(a,b,c);//�����µ����������һ��ֵ�洢��x��
		yy=(long double)c/b;//yyΪ0��1�������
		xx=(long double)x/b;//xxΪ0��1�����������yy���һλ
		py+=yy;//��a{n+1}������
		px+=xx;//��a{n}������
		pxx+=xx*xx;//��a{n}^2������
		pxy+=xx*yy;//��a{n}*a{n+1}������
		}
		cl=(pxy/n-(px/n)*(px/n))/(pxx/n-(px/n)*(px/n));//���������ϵ��
		return cl;//���ض�����ϵ��
}

long double paleo(int a,int b,int c,int n){//������ľ����Լ��飨���ؿ����ֲ�ֵ��
	int i,k,group[1000]={0};
	 long double x,frequency,xk=0;
	 for(i=0;i<n;i++){
		 x=(long double)c/b;
		 c=self_random(a,b,c);
		 k=(int)(1000*x);
		 group[k]++;//�������������ͳ��+1
	 }
	 frequency=(long double)n/1000;//����Ƶ��
	 for(i=0;i<1000;i++)
		 xk+=pow(group[i]-frequency,2)/frequency;//���㿨���ֲ�ֵ
	 return xk;
}

void main() {
	int a=16807,b=2147483647,c=1;//16807������ϵ��
	int aa=329,bb=100000001,cc=1;//RA�������������ϵ��
	int j,n;
	int mod[14]={1500,7500,15000,75000,150000,750000,1500000,7500000,15000000,30000000,60000000,120000000,240000000,800000000};//һЩ�ܵ���ֵ
	FILE *fx;//�����ļ�
	if ((fx=fopen("�����.dat","w+"))==NULL){
		printf("cannot open this file\n");
		exit(0);
	}
	n=15000000;//ȡһ������10000000���ܵ���ֵ�����ڼ��������ϵ��
	fprintf(fx,"self_random C(l)=%.15f    RA_random C(l)=%.15f\n",homo(a,b,c,n),homo(aa,bb,cc,n));//���16807��RA������������Ķ�����ϵ��
	fprintf(fx,"    summation     self_random        RA_random\n");
	for(j=0;j<9;j++){//ȡ��ͬ���ܵ���ֵ���㿨���ֲ�ֵ
	fprintf(fx,"%10d%18.6f%18.6f\n",mod[j],paleo(a,b,c,mod[j]),paleo(aa,bb,cc,mod[j]));//����ܵ���ֵ��������������������ԵĿ����ֲ�ֵ
	}
	fclose(fx);
	printf("the running accomplished successfully\n");//��ʾ�������
}