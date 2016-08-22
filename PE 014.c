#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void)
{
	clock_t start, finish;
	int longest = 0;
	int terms = 0;
	int i;
	unsigned long j;
	start = clock();
	for (i = 1; i <= 1000000; i++)
	{
		j = i;
		int this_terms = 1;
		while (j != 1)
		{
			this_terms++;
			if (this_terms > terms)
			{
				terms = this_terms;
				longest = i;
			}
			if (j % 2 == 0)
			{
				j = j / 2;
			}
			else
			{
				j = 3 * j + 1;
			}
		}
	}
	finish = clock();
	printf("Starting number %d, under one million, produces the longest chain with length %d\n", longest, terms);
	printf("Elapsed time is %f seconds\n", (double)(finish - start) / 1000);
	system("pause");
	return 0;
}