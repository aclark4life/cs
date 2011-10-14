#include<stdio.h>

main(int argc, char **argv)
{
	int a, b, c;
 	if (argc == 4)
	{	
	/*	printf("%s\n",argv[1]);
		printf("%s\n",argv[2]);
		printf("%s\n",argv[3]); */
		a=atoi(argv[1]);
		b=atoi(argv[2]);
		c=atoi(argv[3]);
		if((a == b) && (b==c))printf("equilateral\n");
		if(
			((a==b) && !(b==c)) || 
			((b==c) && !(b==a)) || 
			((a==c) && !(a==b))     ) printf("isosceles\n");

		if(!(a == b) && !(b==c) && !(a==c))printf("scalene\n");
	}	
	else
	{
		printf("usage:\n");
		exit(0);
	}

	/*	if (!strcmp(argv[1],"1")) 
	{
		printf("foo\n");
	}
	*/
	



}
