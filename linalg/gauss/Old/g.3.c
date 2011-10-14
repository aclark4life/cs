/* g.c - Solve an m x (n+1) system of equations
 * with Gauss-Jordan elimination . 
 * Alex Clark - September 1998  .
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NL printf ("\n")
#define NewLine printf ("\n")
#define IMH printf ("i'm here.\n")
double **A; int m,n;
void get_mn();
void get_mem();
void get_mtrx();
void gaussj();
void divide(int r,int c);
void subtract(int i,int j,int k);
void swap(int r,int c); 
void echo_system();

void gaussj() 
{
        int i,j,k;
        for (i=j=1; i<=m && j<=n;j++) 
	{
       		for (k=i; k<=m && A[k][j]==0; k++);
		if (k == m+1) 
		{
			printf ( "%d is a free col\n",j ) ;
		}
		else
		{
			if (i!=k)swap(i,k);
			divide(i,j);
			for ( k = 1 ; k <= m ; k++)
				if ( k != i )subtract(i,j,k);
			i++;
		}
        } 
	if ( i <= m) 
	{
		for ( i = 1; i <= m; i ++ ) 
		{
			for (j = 1; j <= n+1; j++)
			{
				if (A[i][j] !=0 )  
					printf ("no sol\n");
			}
		}

	}
	else
	{
		for ( i = 1 ; i <= m ; i++ ) 
		{

		}
	}

 /*   if  (i <= M and any of the entries A [i .. M] [N + 1] are not zero)
      There are no solutions;
      else
      for  (Each row)
          {
           The variable repesented by the first non-zero entry
           in that row is equal to the last column minus all
           the other non-zero entries in that row times their
           corresponding free variable.
          }
*/

}
void divide(int I,int J)
{
	int i;
	float ans;
	float divisor=A[I][J];
	for (i=i;i<=n;i++) {	
		ans=A[I][i]/divisor;
		A[I][i]=ans; 
	}
}
void subtract(int I,int J,int K)
{
	float ans; 
	int i;
	for (i = 1; i<=m ; i++) {
		if (i!=I) {
			ans=(A[I][J] * -A[i][J]+A[i][J]); 
			A[i][J]=ans; 
		}
	}
}
void swap(int r1,int r2){
	int i,j;
	float *temp = (float *)malloc (n * sizeof (float ) ) ;
	for (i = 1 ; i <= n ; i++ ) {
		temp[i] = A[r1][i]; 
		A[r1][i] = A[r2][i]; 
		A[r2][i] = temp[i]; 
	}
}
void echo_system(){
	int r , c ; 
	for ( r = 1 ; r <=m ; r ++ ) {
		for ( c = 1 ; c <=n ; c ++ ) {
			printf ("%f ",A[r][c]); 
		}NL;
	}
}
void get_mn(){
        int i,j;
	scanf ("%d %d\n",&m,&n);
}
void get_mtrx(){
        int i,j;
        char *tok,*line=(char *)malloc(1024*sizeof(char));
        for (i=1;i<=m;i++){fgets(line,1024,stdin); tok=strtok(line," ");
                for (j=1;tok!=NULL;j++) {
                        A[i][j]=atoi(tok); 
                        tok=strtok(NULL," ");
			//printf ("%f ",A[i][j]);
                } 
		//NL;
        }
}
void get_mem(){
	int i,j;
	A=(double **)malloc((m+1)*sizeof(double *));
        for (i=1;i<=m;i++){
                A[i]=(double *)malloc((n+1)*sizeof(double));
        }
}
void main(int argc)
{
        if (argc!=1){exit(-1);} else {
		get_mn();
		get_mem();
		get_mtrx();
		//echo_system();
		gaussj();
		echo_system();
	}
}
