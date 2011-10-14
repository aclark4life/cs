#define NORM 0 
#define FREE 1 
#define NOSOL 2 
#define ASCII 97
#define NL printf ("\n")
double **A;int m,n,solution=NORM,*mark,*markED,all_zero=0,c=0; 
void Input();
void gaussj();
void Output();
void Solution();
void divide(int i,int j);
void subtract(int i,int j,int k);
void swap(int i,int j); 
