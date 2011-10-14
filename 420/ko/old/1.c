#include<stdio.h>

main()
{

	FILE *infile;
	char *s;
	s=malloc(1024*sizeof(char));
/* ideas :

    for (  ; (fscanf (infile, "%d", &j))!= EOF ;    )
 while( (feof(infile1) != 1) && (feof(infile2) != 1) ) 

*/
	make_array_o_fp();
	do_ls(); 

	infile=fopen("foo","r");

/*	while ((feof(foo) != 1))
		printf("that is something \n");
		*/

	while (fgets(s,1024,infile))
	{
		printf("%s\n",s);
	}

	
/*	while (fgets(s,1,infile)!=NULL)
	{

		printf("%s\n",s);


	}
	*/



}
