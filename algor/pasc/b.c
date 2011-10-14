//Alex Clark
#include <stdio.h>
#define N 10 


int b[N];

int minimum(int i)
{
	int k;
	k = i +1 ; 
	return (k);
}
void init()
{
	int i, j;
	int n = N;
	for (i = 0; i < n; i++)
	{
		for (j = 0 ; j < minimum(i); j++)
		{
			b[i] = 0 ;
		}
	}
}
void main(int argc,char *argv[])
{
	int i , j;
	int n = N;

	init();

	for (i = 0; i <= n; i++)
	{
		for (j=i; j>=0 ; j--)
		{
		   	if ( (j == 0) || (j == i) )
			{
				b[j] = 1;
			}
			else
			{
				b[j] = b[j]+b[j-1];
			}
			printf ( "%d ", b[j] ) ;
		}
		printf ( "\n" ) ;
	}
}
