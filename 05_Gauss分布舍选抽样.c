#include <stdio.h>
#include <math.h>
#include <process.h>
#define pi 3.1415926535897932384626
#define e 2.71828182845904523536
long double gauss(long double x){//Gauss分布函数，返回函数值
	return exp(-0.5*x*x)/sqrt(2*pi);
}
long double trans_lorentz(long double x){//乘系数k=1.521后的Lorentz分布函数，返回函数值
	return 1.521/pi/(1+x*x);
}
int self_random(int a,int b,int c){//返回0到b间的随机数，a为乘子，b为模数，c为上一个随机数的值；
	int q,qq,r,rr,y;
	q=b/a;
	r=b-q*a;//r=(b mod a);
	qq=c/q;
	rr=c-qq*q;//rr=(c mod q);
	y=a*rr-r*qq;
	if(y<0)
		y+=b;
	return y;//新随机数
}
void main(){
	int i,j,n,m,c1,c2;//i,j为计数变量，n为取点次数，m为舍选出的点数，c1，c2为两个随机数列的种子
	int group[2000]={0};//用于存储舍选取样后X变量在[-10,10]按步长0.01分区间计数的数组
	long double u,v;//u,v为[0,1]上均匀分布的随机抽样; 
	long double x,y;//x为按Lorentz分布随机取样的值, y为(0,1.521/pi/(1+x*x))上的均匀分布的随机抽样
	FILE *fgroup;//*fgroup用于存储归一化后数组group[2000]的元素值
	if((fgroup=fopen("group_gauss.dat","w+"))==NULL){
		printf("can not open the file\n");
		exit(0);
	}//创建文件"group_gauss.dat"用于存储归一化后group[2000]的元素值
	printf("input n    ");
	scanf("%d",&n);
	printf("input seed1   ");
	scanf("%d",&c1);
	printf("input seed2   ");
	scanf("%d",&c2);
	for(i=0,m=0;i<n;i++){//进行n次取点
		u=(long double)c1/2147483647;//得到的u为归一化后的随机数
		v=(long double)c2/2147483647;//得到的v为归一化后的随机数
		c1=self_random(16807,2147483647,c1);//生成新随机数
		c2=self_random(16807,2147483647,c2);//生成新随机数
		x=tan(pi*(u-0.5));//x为按Lorentz分布随机取样的值
		y=trans_lorentz(x)*v;//y为(0,1.521/pi/(1+x*x))的均匀分布的随机抽样
		if(y<gauss(x)){//满足取点要求
			m++;//舍选点数值加1
			if(x*x<=100){//统计[-10,10]内的x的子区间分布
				j=(int)100*(10+x);//步长0.01分区间统计
				group[j]++;//对应区间统计值+1
			}
		}
	}
	printf("抽样效率为  %.9f\n",(long double)m/n);
	for(i=m,j=0;j<2000;j++){
		fprintf(fgroup,"%18.16f\n",(long double)group[j]/m);//输出归一化后的数组group[2000]元素值到文件
		i-=group[j];
	}
	if(i==0)
		printf("the worry about the data-overflow is unnecessary\n");
	fclose(fgroup);//关闭文件
	system("pause");
}