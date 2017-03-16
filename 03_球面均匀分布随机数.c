#include <stdio.h>
#include <process.h>
#include <math.h>
#define pi 3.14159265358979323846//�궨��piֵ
void main(){
	long double a,b,x,y,z,theta,phi;//a,bΪ�м����,theta,phiΪ���������,x,y,zΪֱ������ϵ����;
	int i,n;//nΪ�ܵ���,iΪ��������;
	FILE *balltheta,*ballphi,*ballx,*bally,*ballz,*fx;
	 if((balltheta=fopen("ball_theta.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//�����ļ�ball_theta�洢����������theta����;
	 if((ballphi=fopen("ball_phi.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//�����ļ�ball_phi�洢����������phi����;
	 if((ballx=fopen("ball_x.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//�����ļ�ball_x�洢����������x����;
	 if((bally=fopen("ball_y.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//�����ļ�ball_y�洢����������y����;
	 if((ballz=fopen("ball_z.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//�����ļ�ball_z�洢����������z����;
	 if((fx=fopen("�����.dat","r"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//������ҵ01�����в�����0��1��������ļ�
	 printf("input �ܵ��� n   ");
	 scanf("%d",&n);//�����ܵ���nֵ;
	for(i=0;i<n;i++){//����n�������ϵľ��������;
		fscanf(fx,"%lf\n%lf\n",&a,&b);//��������ļ��е������������������������a,b;
		theta=acos(1-2*a);//thetaΪ������ϵ�е�theta���꣬��Χ(0,pi);
		phi=b*2*pi;//phiΪ������ϵ�е�phi���꣬��Χ(0,2pi);
	    z=cos(theta);//�ѿ���ϵ��z�������������µı�ʾ��z=cos(theta);
	    y=sin(theta)*sin(phi);//�ѿ���ϵ��z�������������µı�ʾ��y=sin(theta)*sin(phi);
	    x=sin(theta)*cos(phi);//�ѿ���ϵ��z�������������µı�ʾ��x=sin(theta)*cos(phi);
	    fprintf(ballx,"%12.8f\n",x);//���xֵ���ļ�"ball_x";
	    fprintf(bally,"%12.8f\n",y);//���yֵ���ļ�"ball_y";
	    fprintf(ballz,"%12.8f\n",z);//���zֵ���ļ�"ball_z";
	    fprintf(balltheta,"%12.8f\n",theta);//���thetaֵ���ļ�"ball_theta";
	    fprintf(ballphi,"%12.8f\n",phi);//���phiֵ���ļ�"ball_phi";
	}
	fclose(balltheta);
	fclose(ballphi);
	fclose(ballx);
	fclose(bally);
	fclose(ballz);
	fclose(fx);
	system("pause");
}