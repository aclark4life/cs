#include <stdio.h>
#include <stdlib.h>

main (int argc, char **argv)
{

	if (argc != 2)
	{
		printf("usage: %s upper-bound\n",argv[0]);
		exit(-1);
	}

	srand(getpid());
	printf("%d\n",(rand()%atoi(argv[1]))+1);

	exit(0);
}

