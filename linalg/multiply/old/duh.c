/* m.c - Multiply Two mxn Matrices 
 * Alex Clark - August 1998  
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int m,p,n;
int **A,**B,**C;

void get_first();
void get_matrices();
void get_memory();
void mul_matrices();
void print_out();

void main(int argc, char *argv[]) {
        if (argc!=1) {
                printf("Sorry, I don't take command line arguments.\n");
                exit(-1);
	}
        else {
		get_first();
		get_matrices();
		mul_matrices();
		print_out();
	}
}
void get_matrices()
{
        int i,j;
        char *string=(char *)malloc(2048*sizeof(char));
        char *tokenPtr;
	get_memory();
        for (i=1;i<=m;i++){
                fgets(string,2048,stdin);
		//printf ( "%s\n",string);
                tokenPtr=strtok(string," ");
                for (j=1;tokenPtr!=NULL;j++)
		{
                        A[i][j]=atoi(tokenPtr);
			printf ( "%d ",A[i][j]);
                        tokenPtr=strtok(NULL," ");
		}
        }
/*        for (i=1;i<=p;i++){
                fgets(string,2048,stdin);
		printf ( "%s \n",string);
                tokenPtr=strtok(string," ");
                for (j=1;tokenPtr!=NULL;j++)
		{
                        B[i][j]=atoi(tokenPtr);
			printf ( "%d \n",B[i][j]);
                        tokenPtr=strtok(NULL," ");
		}
        }
*/
}
void mul_matrices() {
        int i,j,k;
	int s = 0;
        for (k=1;k<=    n    ;k++){                 
                for (i=1;i<=   m    ;i++){         
                        for (j=1;j<=  p   ;j++){  
                                s=s+((A[i][j])*(B[j][k]));
                                if (j==p)
				{
                                	C[k][i]=s;
                                }
                        }
			s=0;
                }
	}
}
void get_first()
{
	int i;
	int in[4];
	char *tokenPtr;
        char *string=(char *)malloc(1024*sizeof(char));
	fgets(string,1024,stdin);
        tokenPtr=strtok(string," ");
        for (i=1;tokenPtr!=NULL;i++)
	{
        	in[i]=atoi(tokenPtr);
                tokenPtr=strtok(NULL," ");
		m=in[1]; p=in[2]; n=in[3];
		printf ("m %d, p %d, n %d",m,p,n);
	}
}
void get_memory()
{
	int i,j;

	A=(int **)malloc(m*sizeof(int *));
        for (i=1;i<=p;i++){
                A[i]=(int *)malloc(p*sizeof(int));
        }

        B=(int **)malloc(p*sizeof(int *));
        for (i=1;i<=n;i++){
                B[i]=(int *)malloc(n*sizeof(int));
        }

        C=(int **)malloc(m*sizeof(int *));
        for (i=1;i<=n;i++){
                C[i]=(int *)malloc(n*sizeof(int));
        }
}
void print_out() {
        int i,j;
        for (i=1;i<=m;i++) {
                for (j=1;j<=n;j++) {
                        printf ("%d ",C[j][i]);
                }
        	printf ("\n");
        }
}
