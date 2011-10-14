#include<stdio.h>
main(int argc, char *argv[])
{
	unsigned long int a,b,c;

	if(argc==4)
	{
		prelim_check(argv,1);
		prelim_check(argv,2);
		prelim_check(argv,3);
		a=my_atoi(argv,1);
		b=my_atoi(argv,2);
		c=my_atoi(argv,3);
		is_triangle(a,b,c);
	}
	else
	{
		printf("%s: usage: side1 side2 side3\n",argv[0]);		
	}
}

