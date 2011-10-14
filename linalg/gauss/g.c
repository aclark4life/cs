/* Solve an MxN system of equations using 
 * Gauss-Jordan elimination. 
 * Alex Clark, September 1998.
 *
 * ex. input_file
 * 3 4
 * 1 2 3 4
 * 5 6 7 8
 * 9 10 11 12
 * where '3 4' is 'm n' and everything else is the matrix.
 *
 * ex. command line
 * unix:~>a.out < input_file
 *
 * known bugs: negative zeros in the output.
 *
 *
 *
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"g.h"
void gaussj(){
        int i,j,k;
        for (i=j=1;i<=m+1&&j<n;j++)
	{	
		for(k=i;k<=m&&A[k][j]==0;k++); 
		if(k==m+1)
		{	
			solution=FREE;c++;mark[j]=j;markED[c]=j;
		}
		else
		{	
			if(i!=k)swap(i,k);divide(i,j);
			for (k=1;k<=m;k++)if(k!=i)subtract(i,j,k);
			i++;
		}
        } 
	for (i=1;i<=m;i++)
	{
		for (j=1;j<n;j++)
		{
			if (A[i][j]==0)all_zero++;
			if (A[i][j]==0&&j==n-1&&all_zero==n-1) 
				if(A[i][n]!=0)solution=NOSOL;
		}
		all_zero=0;
	}
}
void Solution(){
	int i,j,k,var=ASCII; 
	switch(solution)
	{
		case NORM:
			for(i=1;i<=m;i++,var++)
			{
				printf("%c=%f\n",var,A[i][n]);
			}
			break;
		case FREE:
			for (i=j=1;i<n;i++,var++)
			{
				if((mark[i])==0)
				{
					printf("%c=%f",var,A[j][n]);
					for(k=1;k<=c;k++)
					{
						if((var-ASCII+1)<markED[k]) 
						{
							printf(" - %f%c",
							A[j][markED[k]],
							markED[k]+ASCII-1);
						}
					}
					NL;
					j++;
				}
				else
				{
					printf("%c=free\n",(mark[i])+(ASCII-1));
				}
			}
			break;
		case NOSOL: 
			printf ("No Solution\n");
			break;
	}
}
void divide(int I,int J){
	int i; float ans,divisor=A[I][J];
	for (i=I;i<=n;i++){ans=A[I][i]/divisor;A[I][i]=ans;}
}
void subtract(int I,int J,int K){
	int i; float factor=A[K][J];
	for (i=J;i<=n;i++){A[K][i]-=(A[I][i]*factor);}
}
void swap(int a,int b){
	int i,j; float *temp=(float*)malloc(n*sizeof(float));
	for (i=1;i<=n;i++){temp[i]=A[a][i];A[a][i]=A[b][i];A[b][i]=temp[i];}
}
void Input(){
        int i,j; char *tok,*line=(char *)malloc(1024*sizeof(char));
	A=(double **)malloc((m+1)*sizeof(double *));
	scanf("%d %d\n",&m,&n);
	mark=(int *)malloc((n)*sizeof(int));
	markED=(int *)malloc((n)*sizeof(int));
        for (i=1;i<=m;i++){A[i]=(double *)malloc((n)*sizeof(double));}
        for (i=1;i<=n;i++){mark[i]=0;markED[i]=0;}
        for (i=1;i<=m;i++){fgets(line,1024,stdin);tok=strtok(line," ");
                for (j=1;tok!=NULL;j++) {
                        A[i][j]=atoi(tok); 
                        tok=strtok(NULL," ");}}
}
void Output(){int i,j;for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){printf("%f ",A[i][j]);}NL;}
}
void main(int argc){if(argc!=1){exit(-1);}else{
	Input();
	gaussj();
	Output();
	Solution();}
}
