#include<stdio.h>
#include<sys/types.h>
#include</usr/ucbinclude/sys/dir.h>
main()
{
	FILE *infile;
	char *buf=(char *)malloc(1024 * sizeof(char *));
	char **scruf=(char **)malloc(sizeof(char *));
	
	int i=0;
	int j=0;
	int n=0;

	system("ls -1 > foo");
	infile=fopen("foo","r");
  	while(fgets(buf,1024,infile)!=NULL)
	{
		n++;
		scruf=(char **)realloc(scruf,sizeof(char *)+n+1);    
/*
		      ||
		    (scruf)
		      ||
		      \/
		       *->string 
		       *->string
		       *->string

			*/

		scruf[n-1]=(char *)malloc(strlen(buf)*sizeof(char));
	        strncpy(scruf[n-1],buf,strlen(buf)-1);
		scruf[n-1][strlen(buf)-1] = '\0';
		printf("%s\n",scruf[i]);
		i++;
	}
	open(scruf,n); 
}
