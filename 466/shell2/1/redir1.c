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
	int pid1;
	int pid2;
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
				if (pipe(fd))
				{
					perror("What is this business...");
					exit(0);
				}
				pid2=fork();
				/*fprintf(stderr,"pid: %d\n",pid2); */
        			switch(pid2)
				{
					case 0:       	tokenv=tokenv+(*tokenc);
							fprintf(stderr,"case 0 executing %s...\n",tokenv[0]); 
							close(0);
							dup(fd[1]);
							/* (*tokenc) = (*tokenc)*/
							/* you set tokenc to 0 at top of this function*/
							/*check for another pipe and recursively call this function if necessary!!*/
							redir(tokenv,tokenc);
							fprintf(stderr,"No redirection.");
							execvp(tokenv[0],tokenv); 
							break;
					
                			default:        close(1);
 							dup(fd[0]);
							fprintf(stderr,"default executing %s...\n",tokenv[0]); 
                					fprintf(stdout,"%s is talking through stdout...\n",tokenv[0]); 
							execvp(tokenv[0],tokenv); 
							break;
				}

 			}
		}
	}
	return(0);
}

