#include<stdio.h>
char **get_files(FILE *infile,char **filev)
{
	char *buf=malloc(1024*sizeof(char));
	int i=0;

	fgets(buf,1024,infile);
	filev[i]=(char*)malloc(strlen(buf)*sizeof(char)); 
	printf("%c",buf[0]); 
	printf("%c",filev[0]);
	strcpy(filev[0],buf);	
	printf("%c",filev[0]); 






/*	while(fgets(buf,1024,infile)!=NULL)
	{
		filev[i]=(char*)malloc(strlen(buf)*sizeof(char)); 
		strcpy(filev[i],"a");
		printf("%c",filev[i]); 
		i++;
	}
	*/
}
