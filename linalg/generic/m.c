/* m.c - Read in and Print out an m x n Matrix.
 * Alex Clark - August 1998  .
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int **A,m,n;
void get_mn();
void get_mem();
void get_mtrx();

void main(int argc) {
        if (argc!=1) { exit(-1); }
        else {
		get_mn();
		get_mem();
		get_mtrx();
	}
}
void get_mn()
{
        int i,j;
	scanf ("%d %d\n",&m,&n);
	printf ("%d %d\n",m,n);
}
void get_mem()
{
	int i,j;
	A=(int **)malloc((m+1)*sizeof(int *));
        for (i=1;i<=m;i++){
                A[i]=(int *)malloc((n+1)*sizeof(int));
        }
}
void get_mtrx()
{
        int i,j;
        char *tok,*line=(char *)malloc(1024*sizeof(char));
        for (i=1;i<=m;i++) {
                fgets(line,1024,stdin);
                tok=strtok(line," ");
                for (j=1;tok!=NULL;j++) {
                        A[i][j]=atoi(tok); printf ("%d ",A[i][j]);
                        tok=strtok(NULL," ");
                } printf ("\n");
        }
}
