#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#define PERMISSIONS 0666

int find_crazy_tokens(char **tokenv, int *tokenc)
{
	int pid; 
	(*tokenc)=0;
	while(tokenv[(*tokenc)]!=NULL)
 	{
		(*tokenc)++;
		if(!strcmp(tokenv[(*tokenc)-1],">"))
		{	
			if(tokenv[(*tokenc)]==NULL)
			{
				free(tokenv[(*tokenc)-1]);
				tokenv[(*tokenc)-1]=NULL;
				execvp(tokenv[0],tokenv); 
				perror(tokenv[0]);
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
				free(tokenv[(*tokenc)-1]);
				tokenv[(*tokenc)-1]=NULL;
				execvp(tokenv[0],tokenv); 
				perror(tokenv[0]);
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
			do_pipe(tokenv,tokenc);
		}
		if(!strcmp(tokenv[(*tokenc)-1],"&"))
		{
			free(tokenv[(*tokenc)-1]);
                       	tokenv[(*tokenc)-1]=NULL;
   			pid=fork();
        		switch(pid)
        		{
 
                		case 0:         /*tokenv=tokenv+(*tokenc); */
                                		printf("find_crazy_tokens execing %s\n",tokenv[0]);
                                		execvp(tokenv[0],tokenv);
 		                                break;
 
                		default:        printf("default\n");
						return(0);
                                		break;
        		}

		}
 	}
	return(0);
}

