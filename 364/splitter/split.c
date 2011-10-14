#include <stdio.h>
#define OUTFILE_DIR "/home/aclark/classes/364/splitter"

/*#define    L_tmpnam        25     */ /* (sizeof(P_tmpdir) + 15) */

main( int argc, char *argv[])
{
  	FILE *infile;
  	FILE *outfile;
  	int i = 0;
  	int j; 
  	char s[L_tmpnam];	 /* (sizeof(P_tmpdir) + 15) */
 
  	if (argc == 2) 
	{
    		infile = fopen(argv[1],"r");
    		if (infile == NULL) 
		{
      			printf("Unable to open the input file.\n");
      			exit (-1);
    		}
    		else 
		{
      			printf("input from %s\n",argv[1]);
    		}
  	}
  	else 
	{
    		infile = stdin;
    		printf ("Input from stdin.\n");
  	}

  	outfile = fopen(tempnam(OUTFILE_DIR,s),"w");
  	for (  ; (fscanf (infile, "%d", &j))!= EOF ;    ) 
	{
    
  		if (i >= j) 
		{  
      			fclose(outfile);
      			outfile = fopen(tempnam(OUTFILE_DIR, s), "w");
    		}
    
    		fprintf(outfile, "%d\n", j);
    		i = j; 
  
	    
	}


}
