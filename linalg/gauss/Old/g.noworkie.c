/* g.c - Solve an m x (n+1) system of equations
 * with Gauss-Jordan elimination . 
 * Alex Clark - September 1998  .
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"g.h"

void sol()
{
	int i,j,var=ASCII_A,free_col; 
	switch(Sol)
	{
		case NORM:
			for (i=1;i<=m;i++,var++){
				//printf("%c=%f\n",var,A[i][n]);
			}
			break;
		case FREE:
			free_col = get_free_col();
			for (i=1;i<=m;i++,var++){
				if ((Free2[i])==0){ 
					printf("%c=%f - %f%c\n",var,A[i][n],A[i][free_col],
							Free2[free_col]+ASCII_A-1);
				}
				else{
					printf("%c=free\n",(Free2[i])+(ASCII_A-1));
				}
			}
			break;
		case NOSOL: 
			printf ("No Solution\n");
			break;
		case 3: break;
	}
}
int get_free_col() {
        int i;
        for (i = 1 ; i <=n ; i++) { if ((Free2[i])!=0) return Free2[i]; }
}
void gaussj(){
        int i,j,k;
        for (i=j=1;i<=m&&j<n;j++) {
       		for(k=i;k<=m&&A[k][j]==0;k++);
		if (k==m+1){
			Sol = FREE;
			free_count++;
			Free[free_count]=j; 
			Free2[j]=j ; 
			
		}
		else{
			if(i!=k)swap(i,k);
			divide(i,j);
			for ( k = 1 ; k <= m ; k++)
				if ( k != i )subtract(i,j,k);
			i++;
		}
        } 
	for (i = 1 ; i <= m ; i++ ) {
		for (j = 1 ; j < n ;j++ ) 
		{
			if (A[i][j]==0) 
			all_zero++;
			if (A[i][j]==0 && j == n-1 && all_zero == n-1 ) 
				if (A[i][n] != 0 ) Sol=NOSOL ; 
		}
		all_zero=0;
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
			A[K][i]-=(A[I][i] * fac); 
	}
}
void swap(int r1,int r2){
	int i,j;
	float *temp=(float*)malloc(n*sizeof(float));
	for (i = 1 ; i <= n ; i++ ) {
		temp[i]=A[r1][i]; 
		A[r1][i]=A[r2][i]; 
		A[r2][i]=temp[i]; 
	}
}
void echo(){
	int i , j ; 
	for ( i = 1 ; i <=m ; i ++ ) {
		for ( j = 1 ; j <=n ; j ++ ) { printf ("%f ",A[i][j]); 
		}NL;
	}
}
void scan(){ int i,j; scanf ("%d %d\n",&m,&n); mem(); }
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
	Free=(int *)malloc((m+1)*sizeof(int));
	Free2=(int *)malloc((m+1)*sizeof(int));
        for (i=1;i<=m;i++){
                A[i]=(double *)malloc((n+1)*sizeof(double));
        }
}
void main(int argc) {
        if (argc!=1){exit(-1);} else {
		scan();
		in();
		gaussj();
		echo();
		sol();
	}
}
