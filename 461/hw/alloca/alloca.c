#include<stdio.h>
#include <stdlib.h>

call_alloca(int x)

{
	x=(int)malloc(sizeof(int));	
	return(x);
}

main (int argc, char *argv) 
{
	int c;
	int i;

	for ( i=0; i<1000000; i++)
	{
	
		call_alloca(c);
	}
}	 
