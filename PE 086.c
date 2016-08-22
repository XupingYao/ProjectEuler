#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(void)
{
	clock_t start,finish;
	int M=1;
	int N=0,Nmax=1000000;
	int x,y,b;
	double yd,bd;
	start=clock();
	while (N<=Nmax)
	{
		M=M+1;
		for (x=1;x<=M;x++)
		{
			yd=((double)(M*M))/x;
			if (floor(yd)==yd)
			{
				y=(int)yd;
				bd=((double)(y-x))/2;
				if (floor(bd)==bd && bd<=(double)2*M)
				{
					b=(int)bd;
					if (1>(b-M))
					{
						N=N+(int)floor(bd/2);
					}
					else
					{
						N=N+(int)floor(bd/2)+1-(b-M);
					}
				}
			}

		}

	}
	printf("The least value of M is %d\n",M);
	finish=clock();
	printf("time used is %f s\n",(double)(finish-start)/1000);
	system("pause");
	return 0;
}