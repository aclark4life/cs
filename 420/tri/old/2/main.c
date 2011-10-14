#include<stdio.h>
/*
	1. make sure all command line entries are digits
	2. make sure digits are a triangle
	3. make sure that digits don't exceed boundaries of... */

main(int argc, char **argv)
{
	int a,b,c;
	char *d;
	char *e;
	char *f;
 	if (argc==4)
	{	
		a=atoi(argv[1]); 
		b=atoi(argv[2]);
		c=atoi(argv[3]);
		d=argv[1];
		e=argv[2];
		f=argv[3];
		/*if((validate_input(d,e,f))==0)check_triangle(a,b,c);  */
/*		validate_input(d,e,f);  */ 
  		check_triangle(a,b,c);
	}	
	else
	{
		printf("usage: side1 side2 side3\n");
		exit(0);
	}
}
