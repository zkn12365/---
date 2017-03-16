#include <stdio.h>
#include <process.h>
#include <math.h>
void main(){
	long double u,v,r2,x,y,z;//u,vΪ�м����,r2=u^2+v^2,x,y,zΪֱ������ϵ����;
	int i,j,k,n;//nΪ�ܵ���,i,j,kΪ��������;
	int group[20][20]={0};//ͳ���������XYƽ��ͶӰ��С����ֲ�
	FILE *ballx,*bally,*ballz,*fx,*fgroup;
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
	if((fgroup=fopen("group.dat","w+"))==NULL){
		printf("cannot open this file\n");
		exit(0);
	}//�����ļ�group�洢XY�����20*20��������ķֲ�����
    if((fx=fopen("�����.dat","r"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//������ҵ01�����в�����0��1��������ļ�
	 printf("input n   ");
	 scanf("%d",&n);//�����ܵ���ֵ
	 for(i=0;i<n;){
		 fscanf(fx,"%lf\n%lf\n",&u,&v);//����������ļ�������
		 u=2*u-1;
		 v=2*v-1;//��Χ��Ϊ-1��1
		 r2=u*u+v*v;
		 if(r2<=1){//����
			 x=2*u*sqrt(1-r2);//����ΪMarsaglia��������
			 y=2*v*sqrt(1-r2);
			 z=1-2*r2;
		 	 fprintf(ballx,"%.15f\n",x);//����������X�������ļ�
			 fprintf(bally,"%.15f\n",y);//����������Y�������ļ�
			 fprintf(ballz,"%.15f\n",z);//����������Z�������ļ�
			 i++;
			 j=(int)10*(x+1);
			 k=(int)10*(y+1);
			 group[j][k]++;//X,Y�����Ӧλ�õ�ͳ��ֵ+1
		 }
		 else i++;
	 }
	 for(j=0;j<20;j++){//��ѭ����Ŀ�������XY����ֲ�������ļ�
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

