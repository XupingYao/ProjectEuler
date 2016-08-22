#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define kmax 12000
int n[kmax + 1];

void foo(int p, int s, int c, int start)
{
	int i;
	int k = p - s + c;
	if(k <= kmax)
		{
			if(n[k] > p)
				{
					n[k] = p;
				}
			for (i = start; i <= 2 * kmax / p; i++)
			{
				foo(p*i, s + i, c + 1, i);
			}
		}
}

int mycomp(const void * p1, const * p2)
{
	const int * a1 = (const int *)p1;
	const int * a2 = (const int *)p2;
	if (*a1 < *a2)
		return -1;
	else if (*a1 == *a2)
		return 0;
	else
		return 1;
}

int main(void)
{
	clock_t start, finish;
	int index;
	int sum;
	start = clock();
	for (index = 0; index <= kmax; index++)
	{
		n[index] = 2 * index;
	}
	foo(1,1,1,2);
	qsort(n, kmax+1, sizeof(int), mycomp);
	index = 2;
	sum = n[index];
	while (index < kmax)
	{
		if (n[index+1] > n[index])
		{
			sum = sum + n[index + 1];
		}
		index = index + 1;
	}
	finish = clock();
	printf("The sum of all the minimal product-sum numbers when k <= %d is\n%d\n", kmax, sum);
	printf("Time used is %f s\n", (double)(finish - start) / 1000);
	system("pause");
	return 0;
}