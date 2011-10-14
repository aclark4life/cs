/* m.c - Find the Determinant of an m x n Matrix. 
   Alex Clark - August 1998  */

#include<stdio.h>
#include<string.h>
#include<assert.h>

int N;
double **A,Ans;

void get_matrx();
void get_easy();
double Det(double **A);
double **get_mem(double **A);

void main()
{
	get_matrx();
	Ans=Det(A);
}
double Det(double **a)
{
	int c,i,k,j,p;
	double **b=NULL;
	double ans;

	if (N <= 3) {
		get_easy();
	}
	else
	{
		b=get_mem(b);
		assert (b!=NULL);
		ans=0;
		for ( i = 1 ; i <= N ; i++)
		{
			c = 0 ;
			for (j= 1 ; j <= N; j++)
			{
				if (j==1)	
				{
					//printf ("[%d][%d]\n",i,j);
				}
				for (k= 1 ; k <= N; k++)
				{
					//printf ( "[%d][%d][%d]\n" , i,j,k ) ;
					if (k != i )	
					{
						//try to assign minor of a to b!
						//b[c++][k] = a[j][k];
						//printf ( "%f " , a[j][k] ) ;
					}
				}
					//printf ("\n");
					//printf ( "[%d][%d][%d]\n" , i,j,k ) ;
			}
					//printf ("\n");
		}
		//Ans += a[i][j] * p * Det(b);
	}
	free (b);
	return (ans);
}
void get_matrx()
{
        int i,j ;
        char *line=(char *)malloc(1024*sizeof(char));
        char *tok;

        fgets( line, 1024, stdin);
	N=atoi(line);

	A=get_mem(A);

        for(i=1;i<=N;i++)
        {
                fgets (line , 1024 , stdin ) ;
                tok=strtok(line, " ");
                for (j=1; tok !=NULL; j++)
                {
                        A[i][j]=atoi(tok);
                        //printf ("%f ",A[i][j]);
                        tok=strtok (NULL, " ");
                } //printf ("\n");
        }
                 //printf ("\n");
}
double **get_mem(double **a)
{
        int i;
        a = (double **)malloc((N+1)*sizeof(double *));
        for (i = 1;i<=(N+1);i++)
        { 
		a[i]= (double *) malloc ((N+1)*sizeof(double)); 
	}
	return (a);
}

void get_easy()
{
	switch(N)
       	{
               case 1:  	printf ("%f\n",A[1][1] ) ; //if A=[a11] is a 1x1 matrix, then det (A) = a11.
                               	break;
               case 2:	  	printf ("%f\n",(A[1][1]*A[2][2])-(A[1][2]*A[2][1]) ) ; //if A=[a22] is a 2x2 
								//   matrix, then det(A) = a11*a22 - a12*a21 . 
				break;
               case 3:	  	printf ("%f\n",((A[1][1]*A[2][2]*A[3][3]) + 
				       (A[1][2]*A[2][3]*A[3][1]) +
				       (A[1][3]*A[2][1]*A[3][2]) -
				       (A[1][1]*A[2][3]*A[3][2]) -
				       (A[1][2]*A[2][1]*A[3][3]) -
				       (A[1][3]*A[2][2]*A[3][1])  ) );
				break;
       	}
} 
