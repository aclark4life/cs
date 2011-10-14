#include<stdio.h>
void open(char **scruf,int n)
{
	int i;



   /*  	char *buf=(char *)malloc(1024 * sizeof(char *));
    	char **file=(char **)malloc(1024 * sizeof(char *));
	char *temp=(char *)malloc(1024 * sizeof(char *));
	*/


	FILE *infile;

	for(i=0;i<1;i++)
	{
		printf("\nthe first file: %s\n",scruf[i]); 
		if (infile=fopen(scruf[i],"r"))
		{
			printf("works, opened %s\n",scruf[i]);
			printf("the pointer is -> %d\n",infile);
		}
		else
		{
			printf("didn't open %s\n",scruf[i]);
			printf("the pointer is -> %d\n",infile);
		}

	/* 	while(fgets(buf,1024,infile)!=NULL)
        	{
                	file[i]=realloc(scruf[i],((strlen(buf))*sizeof(char)));
                	strcpy(file[i],buf);
                	printf("%s",file[i]);
                	i++;
        	}
		*/
	}
}

