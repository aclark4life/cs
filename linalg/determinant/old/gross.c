#include<stdio.h>
#include<string.h>

int **M;
int n;
void read_matrx();
void if_all_zero();
void save_ij();
int I[1024];
int J[1024]; 
int IJcount=0;

int **mem_chores(int **arg);

void main()
{
	read_matrx();
	if (IJcount != 0 ) if_all_zero();


}
void save_ij(int i, int j)
{
	I[IJcount] = i ; 
	J[IJcount] = j ;
}
void read_matrx()
{
        int i,j ;
        char *line = (char *)malloc(1024*sizeof(char));
        char *tok;

        scanf("%d\n",&n);printf("%d\n",n);
        M=mem_chores(M);
        for(i=1;i<=n;i++)
        {
                fgets (line , 1024 , stdin ) ;
                tok=strtok(line, " ");
                for (j=1; tok !=NULL; j++)
                {
                        M[i][j]=atoi(tok);
			if (M[i][j]==0)
			{
				save_ij(i,j);
				IJcount++;
			}
                        printf ("%d ",atoi(tok));
                        tok=strtok (NULL, " ");
                } printf ("\n");
        }
}
int **mem_chores(int **arg)
{
        int i;
        arg = (int **)malloc((n+1)*sizeof(int *));
        for (i = 1;i<=(n+1);i++)
        { arg[i]= (int *) malloc ((n+1)*sizeof(int)); }
        return(arg);
}
void if_all_zero()
{
	int i,j;

 for (j = 0 ; j <= IJcount ; j++)
 {

        for(i=1;i<=n;i++)
        {
		printf ( "%d ",M[   I[j]   ][i] 	);
	}
		printf ("\n");
        for(i=1;i<=n;i++)
        {
		printf ( "%d ",M[   J[j] ][i] 	);
	}
		printf ("\n");
 }
}
