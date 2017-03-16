#include <stdio.h>
#include <process.h>
#include <math.h>
void main(){
	long double u,v,r2,x,y,z;//u,v为中间变量,r2=u^2+v^2,x,y,z为直角坐标系变量;
	int i,j,k,n;//n为总点数,i,j,k为计数变量;
	int group[20][20]={0};//统计随机点在XY平面投影的小区间分布
	FILE *ballx,*bally,*ballz,*fx,*fgroup;
	 if((ballx=fopen("ball_x.dat","w+"))==NULL){
		 printf("cannot open this file\n");
    	 exit(0);
	 }//创建文件ball_x存储球面随机点的x坐标;
	 if((bally=fopen("ball_y.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//创建文件ball_y存储球面随机点的y坐标;
	 if((ballz=fopen("ball_z.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//创建文件ball_z存储球面随机点的z坐标;
	if((fgroup=fopen("group.dat","w+"))==NULL){
		printf("cannot open this file\n");
		exit(0);
	}//创建文件group存储XY坐标的20*20个子区间的分布计数
    if((fx=fopen("随机数.dat","r"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//调用作业01程序中产生的0至1的随机数文件
	 printf("input n   ");
	 scanf("%d",&n);//键入总点数值
	 for(i=0;i<n;){
		 fscanf(fx,"%lf\n%lf\n",&u,&v);//调用随机数文件的数据
		 u=2*u-1;
		 v=2*v-1;//范围变为-1至1
		 r2=u*u+v*v;
		 if(r2<=1){//抽样
			 x=2*u*sqrt(1-r2);//以下为Marsaglia抽样方法
			 y=2*v*sqrt(1-r2);
			 z=1-2*r2;
		 	 fprintf(ballx,"%.15f\n",x);//输出随机数的X坐标至文件
			 fprintf(bally,"%.15f\n",y);//输出随机数的Y坐标至文件
			 fprintf(ballz,"%.15f\n",z);//输出随机数的Z坐标至文件
			 i++;
			 j=(int)10*(x+1);
			 k=(int)10*(y+1);
			 group[j][k]++;//X,Y坐标对应位置的统计值+1
		 }
		 else i++;
	 }
	 for(j=0;j<20;j++){//该循环的目的是输出XY坐标分布情况至文件
		 for(k=0;k<20;k++)
		 fprintf(fgroup,"%10d",group[j][k]);
		 fprintf(fgroup,"\n");
	 }
	fclose(ballx);
	fclose(bally);
	fclose(ballz);
	fclose(fgroup);
	fclose(fx);
    system("pause");
}

