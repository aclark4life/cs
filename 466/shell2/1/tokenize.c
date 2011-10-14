#include<stdio.h>
#define SEPARATOR " \t"

char **tokenize(char *s,int *tokenc)
{
	char *token;
	char *temp;
	char **tokenv=(char **)malloc(sizeof(char *));

	(*tokenc)=0;
	token=strtok(s,SEPARATOR);
	if (token!=NULL)
	{
		(*tokenc)++;
		temp=(char *)malloc((strlen(token)+1)*sizeof(char));
		strcpy(temp,token);
		tokenv[(*tokenc)-1]=temp;
	}
	else
	{
		tokenv[0]=NULL;
		return(tokenv);
	}

	while((token=token=strtok(NULL,SEPARATOR))!=NULL)
	{
		(*tokenc)++;
		tokenv=realloc(tokenv,(sizeof(char *)*(*tokenc)));
		temp=(char *)malloc((strlen(token)+1)*sizeof(char));
		strcpy(temp,token);
		tokenv[(*tokenc)-1]=temp;
	}
	tokenv=realloc(tokenv,(sizeof(char *)*(*tokenc)+1));
	tokenv[(*tokenc)]=NULL;
	return (tokenv);
}
