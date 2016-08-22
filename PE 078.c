#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 55375
int main(void)
{
	clock_t start,finish;
	int p[N];
	int n,k,i,j;
	start=clock();
	p[0]=p[1]=1;
	for(n=2;n<N;n++)
	{
		p[n]=0;
		for(k=1;k<=(1+sqrt(1.0+24.0*n))/6;k++)
		{
			i=(int)(n-k*(3*k-1)/2);
			j=(int)(n-k*(3*k+1)/2);
			if(j>=0)
				p[n]=p[n]+pow(-1.0,k+1)*(p[i]+p[j]);
			else
				if(i>=0)
					p[n]=p[n]+pow(-1.0,k+1)*(p[i]);
		}
		//p[n]=(int)fmod((double)p[n],1000000.0);
		p[n]=p[n]%1000000;
		if(p[n]==0)
		{
			printf("p[%d]=%d\n",n,p[n]);
			break;
		}
	}
	finish=clock();
	printf("time used is %f s\n",(double)(finish-start)/1000);
	system("pause");
	return 0;
}