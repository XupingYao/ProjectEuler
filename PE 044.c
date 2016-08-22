#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	clock_t start,finish;
  unsigned long long int D=0, Pd, e;
  unsigned long long int i=0, j, r, d, f;
  start=clock();
  while(1)
  {
    D += 3*i++ + 1;
    Pd = 0;
    for(d=1 ; d<i ; d++)
    {
      Pd += 3*d-2;
      j = (D-Pd)/(3*d);
      r = (D-Pd)%(3*d);
      if(r==0)
      {
        e = 1 + 24*(j*(3*j-1)+D);
        f = round(sqrt((double)e));
        if( (f*f==e) & ((1+f)%6==0) )
        {
          printf("the value of D is equal to %llu\n", D);
          finish=clock();
				  printf("time used is %f s\n",(double)(finish-start)/1000);
				  system("pause");
          return 0;
        }
      }
    }
  }
}