#include <stdio.h>
#define N 7
#define INT_MAX 99999      // if i use the real INT_MAX, then when i perform
						   // addition the value flips, ie becomes negative.
#define LIM N+1

int W[N+1][N+1];
int D[N+1][N+1];
int P[N+1][N+1];

void print()
{
	int i,j;

	printf ( "W:\n");
	for ( i = 0 ; i <LIM; i++ ) 
	{
		for ( j = 0 ; j <LIM ; j++ ) 
		{
			printf ( "%d " , W[i][j] ) ;
		}
		printf ( "\n");
	}

	printf ( "D:\n");
	for ( i = 0 ; i <LIM; i++ ) 
	{
		for ( j = 0 ; j<LIM ; j++ ) 
		{
			printf ( "%d " , D[i][j] ) ;
		}
		printf ( "\n");
	}

	printf ( "P:\n");
	for ( i = 0 ; i <LIM; i++ ) 
	{
		for ( j = 0 ; j<LIM ; j++ ) 
		{
			printf ( "%d " , P[i][j] ) ;
		}
		printf ( "\n");
	}
}
void floyd2()
{
	int i, j , k;

	for ( i = 0 ; i <LIM; i++ )  				// copy W to D
	{
		for ( j = 0 ; j<LIM ; j++ ) 
		{
			D[i][j]=W[i][j];
		}
	}

	for ( k = 1 ; k <LIM ; k++ )   			// run floyd's algorithm
	{
		for ( i = 1 ; i <LIM; i++ ) 
		{
			for ( j = 1 ; j<LIM ; j++ ) 
			{
				if ( (D[i][k]+D[k][j])  < D[i][j] ) 
				{
					P[i][j] = k; 
					D[i][j] = D[i][k] + D[k][j] ;
				}
			}
		}
	}
}
fill()									// this is ABSOLUTELY horrendous and the WORST possible way to do this
										// but hey, i have a job.
{
	int i,j ;
	for (i = 0; i < LIM; i ++ ) 
	{
		for (j = 0; j < LIM; j++) 
		{
			if(i==0) W[i][j] = -1 ;
			if(j==0) W[i][j] = -1 ; 

			if(i==0) P[i][j] = -1 ;
			if(j==0) P[i][j] = -1 ; 

			if (( i == 1 )&&( j == 2 )) W[i][j] =  4 ;
			if (( i == 1 )&& ( j == 3 )) W[i][j] = INT_MAX;
			if (( i == 1 )&& ( j == 4 )) W[i][j] = INT_MAX ;
			if (( i == 1 )&& ( j == 5 )) W[i][j] = INT_MAX ;
			if (( i == 1 )&& ( j == 6 )) W[i][j] = 10 ;
			if (( i == 1 )&& ( j == 7 )) W[i][j] = INT_MAX ;

			if (( i == 2 )&&( j == 1 )) W[i][j] =  3 ;
			if (( i == 2 )&& ( j == 3 )) W[i][j] = INT_MAX;
			if (( i == 2 )&& ( j == 4 )) W[i][j] = 18 ;
			if (( i == 2 )&& ( j == 5 )) W[i][j] = INT_MAX ;
			if (( i == 2 )&& ( j == 6 )) W[i][j] = INT_MAX ;
			if (( i == 2 )&& ( j == 7 )) W[i][j] = INT_MAX ;

			if (( i == 3 )&&( j == 1 )) W[i][j] =  INT_MAX ;
			if (( i == 3 )&& ( j == 2 )) W[i][j] = 6 ; 
			if (( i == 3 )&& ( j == 4 )) W[i][j] = INT_MAX ;
			if (( i == 3 )&& ( j == 5 )) W[i][j] = INT_MAX ;
			if (( i == 3 )&& ( j == 6 )) W[i][j] = INT_MAX ;
			if (( i == 3 )&& ( j == 7 )) W[i][j] = INT_MAX ;

			if (( i == 4 )&&( j == 1 )) W[i][j] =  INT_MAX ;
			if (( i == 4 )&& ( j == 2 )) W[i][j] = 5;
			if (( i == 4 )&& ( j == 3 )) W[i][j] = 15 ;
			if (( i == 4 )&& ( j == 5 )) W[i][j] = 2 ;
			if (( i == 4 )&& ( j == 6 )) W[i][j] = 19 ;
			if (( i == 4 )&& ( j == 7 )) W[i][j] = 5 ;

			if (( i == 5 )&&( j == 1 )) W[i][j] = INT_MAX ;
			if (( i == 5 )&& ( j == 2 )) W[i][j] = INT_MAX;
			if (( i == 5 )&& ( j == 3 )) W[i][j] = 12 ;
			if (( i == 5 )&& ( j == 4 )) W[i][j] = 1 ;
			if (( i == 5 )&& ( j == 6 )) W[i][j] = INT_MAX ;
			if (( i == 5 )&& ( j == 7 )) W[i][j] = INT_MAX ;

			if (( i == 6 )&&( j == 1 )) W[i][j] = INT_MAX ;
			if (( i == 6 )&& ( j == 2 )) W[i][j] = INT_MAX;
			if (( i == 6 )&& ( j == 3 )) W[i][j] = INT_MAX ;
			if (( i == 6 )&& ( j == 4 )) W[i][j] = INT_MAX ;
			if (( i == 6 )&& ( j == 5 )) W[i][j] = INT_MAX ;
			if (( i == 6 )&& ( j == 7 )) W[i][j] = 10 ;

			if (( i == 7 )&&( j == 1 )) W[i][j] = INT_MAX ;
			if (( i == 7 )&& ( j == 2 )) W[i][j] = INT_MAX;
			if (( i == 7 )&& ( j == 3 )) W[i][j] = INT_MAX ;
			if (( i == 7 )&& ( j == 4 )) W[i][j] = 8 ;
			if (( i == 7 )&& ( j == 5 )) W[i][j] = INT_MAX ;
			if (( i == 7 )&& ( j == 6 )) W[i][j] = INT_MAX ;
		}
	}
}
init()			//init
{
	int i,j ;
	for (i = 0; i < LIM ; i ++ ) 
	{
		for (j = 0; j < LIM ; j++) 
		{
			W[i][j] = 0;
			D[i][j] = 0;
			P[i][j] = 0 ;
		}
	}
}
void main () 		// ahhh... nothing in main but functions.
{
	init();
	fill();
	floyd2();
	print();
}
