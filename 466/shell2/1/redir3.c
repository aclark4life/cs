/* redir.c */
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#define PERMISSIONS 0666

int redir(char **tokenv, int *tokenc)
{
	int fd[2];
	int pid;
	int status;
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
			free(tokenv[(*tokenc)-1]);
			tokenv[(*tokenc)-1]=NULL;
			if(tokenv[(*tokenc)]==NULL)
			{
				execvp(tokenv[0],tokenv); 
			}
			else
			{
				if (pipe(fd)==-1)
				{
					perror("pipe error");
					exit(0);
				}
				pid=fork();
        			switch(pid)
				{
					case 0:         tokenv=tokenv+(*tokenc);         
							close(0); 			
							dup(fd[1]); 		
							/*redir(tokenv,tokenc);  */
							/*fprintf(stderr,"case 0 executing %s...\n",tokenv[0]); */
							execvp(tokenv[0],tokenv); 
							perror(tokenv[0]);
							close(fd[1]);
							break;
                			default:       	close(1);	
 							dup(fd[0]);    
							/*fprintf(stderr,"default executing %s...\n",tokenv[0]); */
							execvp(tokenv[0],tokenv); 
							perror(tokenv[0]);
							close(fd[0]);
							break;
				}
				break;

 			}
		}
	}
	return(0);
}

