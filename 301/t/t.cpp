#include <stdio.h>



int foo();  

	int in_bowl[5];


void main()
{


	in_bowl[0] = 1;
	in_bowl[1] = 1;
	in_bowl[2] = 1;
	in_bowl[3] = 1;
	in_bowl[4] = 1;


	printf ("%d\n",in_bowl[0] ) ;
	printf ("%d\n",in_bowl[0] ) ;
	printf ("%d\n",in_bowl[0] ) ;
	printf ("%d\n",in_bowl[0] ) ;
	printf ("%d\n",in_bowl[0] ) ;


	// const { return foo[0] ; }

}

int foo() { return in_bowl[0]; } 
