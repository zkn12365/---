#include <stdio.h>
#include <process.h>
#include <math.h>
#define pi 3.14159265358979323846//宏定义pi值
void main(){
	long double a,b,x,y,z,theta,phi;//a,b为中间变量,theta,phi为球坐标变量,x,y,z为直角坐标系变量;
	int i,n;//n为总点数,i为计数变量;
	FILE *balltheta,*ballphi,*ballx,*bally,*ballz,*fx;
	 if((balltheta=fopen("ball_theta.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//创建文件ball_theta存储球面随机点的theta坐标;
	 if((ballphi=fopen("ball_phi.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//创建文件ball_phi存储球面随机点的phi坐标;
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
	 if((fx=fopen("随机数.dat","r"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//调用作业01程序中产生的0至1的随机数文件
	 printf("input 总点数 n   ");
	 scanf("%d",&n);//键入总点数n值;
	for(i=0;i<n;i++){//产生n个球面上的均匀随机数;
		fscanf(fx,"%lf\n%lf\n",&a,&b);//从随机数文件中调用两个相邻随机数赋给变量a,b;
		theta=acos(1-2*a);//theta为球坐标系中的theta坐标，范围(0,pi);
		phi=b*2*pi;//phi为球坐标系中的phi坐标，范围(0,2pi);
	    z=cos(theta);//笛卡尔系中z坐标在球坐标下的表示：z=cos(theta);
	    y=sin(theta)*sin(phi);//笛卡尔系中z坐标在球坐标下的表示：y=sin(theta)*sin(phi);
	    x=sin(theta)*cos(phi);//笛卡尔系中z坐标在球坐标下的表示：x=sin(theta)*cos(phi);
	    fprintf(ballx,"%12.8f\n",x);//输出x值到文件"ball_x";
	    fprintf(bally,"%12.8f\n",y);//输出y值到文件"ball_y";
	    fprintf(ballz,"%12.8f\n",z);//输出z值到文件"ball_z";
	    fprintf(balltheta,"%12.8f\n",theta);//输出theta值到文件"ball_theta";
	    fprintf(ballphi,"%12.8f\n",phi);//输出phi值到文件"ball_phi";
	}
	fclose(balltheta);
	fclose(ballphi);
	fclose(ballx);
	fclose(bally);
	fclose(ballz);
	fclose(fx);
	system("pause");
}