/* g.c - Solve an m x (n+1) system of equations
 * with Gauss-Jordan elimination . 
 * Alex Clark - September 1998  .
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"fun.h"

void gaussj() {
        int i,j,k;
        for (i=j=1; i<=m && j<n;j++) 
	{
	NL;echo ();
       		for (k=i; k<=m && A[k][j]==0; k++);
		if (k == m+1) {
			printf ( "%d is a free col\n",j ) ;
		}
		else {
			if (i!=k)swap(i,k);
			divide(i,j);
	NL;echo ();
			for ( k = 1 ; k <= m ; k++)
				if ( k != i )subtract(i,j,k);
			i++;
		}
	NL;
	echo ();
        } 
	if ( i <= m){
		for ( i = 1; i <= m; i ++ ) {
			for (j = 1; j <= n+1; j++) {
				if (A[i][j] !=0 )  ;
			}
		}

	}
	else
	{
		for ( i =j= 1 ; i <= m ; i++,j++ ) {
				printf ("A[%d][%d] = %f\n",i,j,A[i][n] ) ;
		}
	}

}
void divide(int I,int J)
{
	int i;
	float ans;
	float divisor=A[I][J];

	for (i=I;i<=n;i++) {	
		ans=A[I][i]/divisor;
		A[I][i]=ans; 
	}
}
void subtract(int I,int J,int K)
{
	float ans; 
	float fac=A[K][J];

	int i;
	for (i = J; i<=n ; i++) {
printf ("i = %d  J = %d  K = %d  I = %d\n", i, J, K, I);
	printf ( "b A[k][i] = %f\n", A[K][i] ) ;
			A[K][i]-=(A[I][i] * fac); 
	printf ( " a A[k][i] = %f\n", A[K][i] ) ;
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
void echo(){
	int i , j ; 
	for ( i = 1 ; i <=m ; i ++ ) {
		for ( j = 1 ; j <=n ; j ++ ) { printf ("%f ",A[i][j]); 
		}NL;
	}
}
void scan(){
        int i,j;
	scanf ("%d %d\n",&m,&n);
}
void in(){
        int i,j;
        char *tok,*line=(char *)malloc(1024*sizeof(char));
        for (i=1;i<=m;i++){fgets(line,1024,stdin); tok=strtok(line," ");
                for (j=1;tok!=NULL;j++) {
                        A[i][j]=atoi(tok); 
                        tok=strtok(NULL," ");
                } 
        }
}
void mem(){
	int i,j;
	A=(double **)malloc((m+1)*sizeof(double *));
        for (i=1;i<=m;i++){
                A[i]=(double *)malloc((n+1)*sizeof(double));
        }
}
void main(int argc) {
        if (argc!=1){exit(-1);} else {
		scan();
		mem();
		in();
		gaussj();
	}
}
