#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
#define pi 3.14159265358979323846264
void main()
{
	int i,j;//i,j为循环变量
	int m,n;//m为迭代次数,n为系数lambda的取值点数
	long double x,xx;//xx为x的初始值,x为每次迭代的结果,在迭代中更新
	long double y;//用于存储不同的lambda值,在循环中更新
	long double a,b;//系数lambda取值区间为[a,b]
	clock_t start,finish;//时间计数变量
	double duration;//存储程序运行时间
	FILE *fx;//文件指针,对应存储所有x值的数据文件
	if((fx=fopen("fencha.dat","w+"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
	}//打开文件
	printf("输入x的初始值    ");
	scanf("%lf",&xx);//键入x的初始值
	printf("输入迭代次数    ");
	scanf("%d",&m);//键入迭代次数
	printf("输入lambda的上界    ");
	scanf("%lf",&b);//键入lambda的上界
	printf("输入lambda的下界    ");
	scanf("%lf",&a);//键入lambda的下界
	printf("输入lambda取点数    ");
	scanf("%d",&n);//键入lambda的取点个数
	start=clock();//计时点1
	for(j=0;j<n;j++)
	{
		x=xx;//对不同的lambda,初始化x
		y=a+(b-a)/(long double)n*j;//lambda的第j+1个取值点的值
		for(i=0;i<100;i++)
			x=y*sin(pi*x);//先行迭代100次,使实际取的x值对应初始值不同
		for(i=0;i<m;i++)
		{
			x=y*sin(pi*x);
			fprintf(fx,"%.8f\n",x);//迭代x,输出至文件
		}
	}
	fclose(fx);//关闭文件
	finish=clock();//计时点2
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("the programme has been running for %.6f seconds\n",duration);//输出程序运行时间
	system("pause");
}