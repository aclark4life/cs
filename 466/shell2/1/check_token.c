#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#define PERMISSIONS 0666

int check_token(char **tokenv, int *tokenc)
{
	(*tokenc)=0;
	while(tokenv[(*tokenc)]!=NULL)
 	{
		(*tokenc)++;
		if(!strcmp(tokenv[(*tokenc)-1],">"))
		{	
			if(tokenv[(*tokenc)]==NULL)
			{
			/*	return(0); */
			}
			else
			{
				free(tokenv[(*tokenc)-1]);
				tokenv[(*tokenc)-1]=NULL;
				close(1); 
				dup(open(tokenv[(*tokenc)],O_WRONLY | O_CREAT,PERMISSIONS)); 
				return(0);  
			
 			}

		} 
		if(!strcmp(tokenv[(*tokenc)-1],"<"))
		{
			if(tokenv[(*tokenc)]==NULL)
			{
			/*	return(0);  */
			} 
			else
			{
				free(tokenv[(*tokenc)-1]);
				tokenv[(*tokenc)-1]=NULL;    
				close(0);
				dup(open(tokenv[(*tokenc)],O_RDONLY)); 
				return(0); 
			}
		}
		if(!strcmp(tokenv[(*tokenc)-1],"|"))
		{
			my_pipe(tokenv,tokenc);
		}
		if(!strcmp(tokenv[(*tokenc)-1],"&"))
		{
			printf ( "background this process!\n");
			exit(0);
		}
	}
	return(0);
}

