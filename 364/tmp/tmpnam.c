#include <stdio.h>

main(int argc, char *argv[])
{
  	char s[L_tmpnam];
  	int i, j;

  	if (argc != 2) 
	{
      		printf("usage: %s n\n", argv[0]);
      		exit (-1);
  	}

  	j = atoi(argv[1]);
  /*	printf("p_tmpdir is %s\n",P_tmpdir); */
  	printf("p_tmpdir is %s\n","/home/aclark/classes/364/tmp"); 
  	printf("L_tmpnam = %d \n",L_tmpnam);
  	printf("TMP_MAX = %d \n",TMP_MAX);
 
 /* 	for (i = 0 ; i <2* TMP_MAX -2; i++) tmpnam(s); */

  	for (i=0; i < j; i++)
    	{
      	/*	tmpnam(s); */
      		printf("%s \t", s); 
      		printf("%s \n", s+9); 
    	}
   	exit(0); 
}  


