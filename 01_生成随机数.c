#include <stdio.h>
#include <process.h>
  self_random(int a, int b,int c){//����0��b����������aΪ���ӣ�bΪģ����cΪ��һ���������ֵ��
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
	int i,a,b,c,n;
     long double p;
	 FILE *fp;
	 if((fp=fopen("�����.dat","w+"))==NULL){
		 printf("cannot open this file\n");
		 exit(0);
	 }//������ļ�
	printf("�������  ");//������������ֵ
	scanf("%d",&a);
	printf("����ģ��  ");
	scanf("%d",&b);
	printf("��������  ");
	scanf("%d",&c);
	printf("���볤��  ");
	scanf("%d",&n);
	for (i=0;i<n;i++){
		c=self_random(a,b,c);//�õ�0��b�������
		p=(long double)c/b;//�������һ��
	    fprintf(fp,"%.15f\n",p);//�����һ�����������ļ�
	}
	fclose(fp);
}

