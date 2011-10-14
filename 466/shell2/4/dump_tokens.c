#include<stdio.h>

void dump_tokens(char **tokenv,int *tokenc)
{
	(*tokenc)=0;
	while(tokenv[(*tokenc)]!=NULL)
	{
		fprintf(stderr,"%s\n",tokenv[(*tokenc)]);
		(*tokenc)++;
	}
}
