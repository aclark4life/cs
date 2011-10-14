#include <stdio.h>

main (int argc, char *argv[])

{
  	int i,n,x;

  	if (argc != 2) 
	{
    		printf("usage: %s x\n",argv[0]);
  	}
  	else 
	{
  		for(i=0;i<strlen(argv[1]);i++)
        	{
                	if(isdigit(argv[1][i])==0)
                	{
                        	printf("%s: input error.\n",argv[1]);
                        	exit(0);
                	}
        	}

    		x = atoi(argv[1]);
    		for (i = 0; i < x; i++)
		{
      			printf("%d\n",random()); 
    		}    
	}
}
