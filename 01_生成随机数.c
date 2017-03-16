#include <stdio.h>
#include <process.h>
  self_random(int a, int b,int c){//返回0到b间的随机数，a为乘子，b为模数，c为上一个随机数的值；
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
	int i,a,b,c,n;
     long double p;
	 FILE *fp;
	 if((fp=fopen("随机数.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//随机数文件
	printf("输入乘子  ");//给几个参数赋值
	scanf("%d",&a);
	printf("输入模数  ");
	scanf("%d",&b);
	printf("输入种子  ");
	scanf("%d",&c);
	printf("输入长度  ");
	scanf("%d",&n);
	for (i=0;i<n;i++){
		c=self_random(a,b,c);//得到0至b的随机数
		p=(long double)c/b;//随机数归一化
	    fprintf(fp,"%.15f\n",p);//输出归一后的随机数至文件
	}
	fclose(fp);
}

