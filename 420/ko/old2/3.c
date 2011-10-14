#include<stdio.h>
#include<sys/types.h>
#include</usr/ucbinclude/sys/dir.h>
#define NUM 10
main()
{
	FILE *infile;
	char *buf=(char *)malloc(NUM * sizeof(char *));
	char **scruf;
/*	char **scruf=(char **)malloc(NUM * sizeof(char *)); */
	struct dir;
/*	DIR *dirp; 


	readdir(dirp);
	*/

	int i=0;

	system("ls > foo");
	infile=fopen("foo","r");
/*
	while((fgets(buf,NUM,infile))!=NULL)
	{
		scruf[i]=realloc(scruf[i],strlen(buf));
		printf("%s\n",scruf[i]); 
		i++;
	}
	*/
	/*
	for(i=0;i<NUM;i++)
	{
		printf("%c\n",buf[i]);
	}
	*/

	for(i=0;i<NUM;i++) 
	{
		fgets(buf,NUM,infile);
/*		scruf[i]=realloc(scruf[i],(NUM * sizeof (char ))); */
		scruf[i]="foo";
		printf("%s\n",scruf[i]);
		printf("%s\n",buf);
	}

}
