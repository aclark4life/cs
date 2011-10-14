#include<stdio.h>

main (int argc, char *argv[])
{
  
  	int a=1000;
  	int asub=0;
  
  	if (argc != 2) exit (-1);
  	else 
	{
    		asub= atoi(argv[1]);
    		printf("%d",asub);
  	}
}
