#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int digitalsquare(int x)
{
	int d,digital,s,i;
	d=(int)floor(log10((double)x));
	s=0;
	for (i = 1; i <= d+1; i++)
	{
		digital=x%10;
		x=(x-digital)/10;
		s=s+digital*digital;
	}
	return s;
}

int main(void)
{
	clock_t start,finish;
	int N=10000000;
	int n=0;
	int l,j,k;
	int idx[567];
	start=clock();
	for (j = 0; j < 567; j++)
	{
		idx[j]=j+1;
	}
	for (j = 0; j < 567; j++)
	{
		while (idx[j]!=1 && idx[j]!=89)
		{
			idx[j]=digitalsquare(idx[j]);
		}
	}
	for (k = 1; k <= N; k++)
	{
		l=digitalsquare(k);
		if (idx[l-1]==89)
		{
			n=n+1;
		}
	}
	printf("The numbers below ten million which will arrive at 89 is \n%d\n",n);
	finish=clock();
	printf("Elapsed time is %f seconds\n",(double)(finish-start)/1000);
	system("pause");
	return 0;
}
