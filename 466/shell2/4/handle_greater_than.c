#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#define PERMISSIONS 0666


int handle_greater_than(char **tokenv, int *tokenc)
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
	}
}


