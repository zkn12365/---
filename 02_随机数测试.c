#include <stdio.h>
#include <process.h>
#include <math.h>
int self_random(int a,int b,int c) {//返回0到b之间的随机数，a为乘子,b为模数,c为上个随机数的值;
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

long double homo(int a,int b,int c,int n){//随机数的独立性检验（返回C(l)系数）
	int i,x;
	long double yy,xx,px=0,py=0,pxx=0,pxy=0,cl;
		for (i=0;i<n;i++){
		x=c;
		c=self_random(a,b,c);//生成新的随机数，上一个值存储在x中
		yy=(long double)c/b;//yy为0至1的随机数
		xx=(long double)x/b;//xx为0至1的随机数，比yy落后一位
		py+=yy;//即a{n+1}项的求和
		px+=xx;//即a{n}项的求和
		pxx+=xx*xx;//即a{n}^2项的求和
		pxy+=xx*yy;//即a{n}*a{n+1}项的求和
		}
		cl=(pxy/n-(px/n)*(px/n))/(pxx/n-(px/n)*(px/n));//计算独立性系数
		return cl;//返回独立性系数
}

long double paleo(int a,int b,int c,int n){//随机数的均匀性检验（返回卡方分布值）
	int i,k,group[1000]={0};
	 long double x,frequency,xk=0;
	 for(i=0;i<n;i++){
		 x=(long double)c/b;
		 c=self_random(a,b,c);
		 k=(int)(1000*x);
		 group[k]++;//子区间内随机数统计+1
	 }
	 frequency=(long double)n/1000;//理论频数
	 for(i=0;i<1000;i++)
		 xk+=pow(group[i]-frequency,2)/frequency;//计算卡方分布值
	 return xk;
}

void main() {
	int a=16807,b=2147483647,c=1;//16807产生器系数
	int aa=329,bb=100000001,cc=1;//RA的随机数产生器系数
	int j,n;
	int mod[14]={1500,7500,15000,75000,150000,750000,1500000,7500000,15000000,30000000,60000000,120000000,240000000,800000000};//一些总点数值
	FILE *fx;//数据文件
	if ((fx=fopen("随机数.dat","w+"))==NULL){
		printf("cannot open this file\n");
		exit(0);
	}
	n=15000000;//取一个大于10000000的总点数值，用于计算独立性系数
	fprintf(fx,"self_random C(l)=%.15f    RA_random C(l)=%.15f\n",homo(a,b,c,n),homo(aa,bb,cc,n));//输出16807和RA随机数产生器的独立性系数
	fprintf(fx,"    summation     self_random        RA_random\n");
	for(j=0;j<9;j++){//取不同的总点数值计算卡方分布值
	fprintf(fx,"%10d%18.6f%18.6f\n",mod[j],paleo(a,b,c,mod[j]),paleo(aa,bb,cc,mod[j]));//输出总点数值，两个随机数产生器各自的卡方分布值
	}
	fclose(fx);
	printf("the running accomplished successfully\n");//提示程序完成
}