#include <stdio.h>
#define N 10 


int b[N][N];
int c[N];
int i, j;
int n = N;
int k = N;


int minimum(int I)
{
	int K;
	K = I +1 ; 

//	printf  ("%d, %d\n", i, j );

//	printf  ("%d\n", K);

//	printf  ("%d\n",  K);
	return (K);

}
void init()
{
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < minimum(i) ; j++)
		{
			b[i][j] = 0;
		}
	}
}
void init_c()
{
	for (i = 0; i < n; i++)
	{	
		c[i] = 0;
	}
}


void main(int argc,char *argv[])
{
	init();

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < minimum(i) ; j++)
		{
			if (  (j == 0) || (j == i) ) 
			{
	//			printf (" well then \n");
	//			printf (" i = %d\n",i);
	//			printf (" j = %d\n",j);

		 		b[i][j] = 1;
			}
			else
			{
//				printf (" j != 0 and j != i, right? \n");
//				printf (" i = %d\n",i);
////			printf (" j = %d\n",j);
//				printf ("%d %d\n",i,j ) ;
			//	printf ( "%d ", b[i-1][j-1] ) ;

				b[i][j] = ( b[i-1][j-1] + b[i-1][j] ) ;

			}
			printf ( "%d ", b[i][j] ) ;
			
		}
		printf ( "\n");
	}
}
