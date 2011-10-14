#include<stdio.h>
my_pipe(char **tokenv,int *tokenc)
{
   	int fd[2];
   	int pid;

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
					check_token(tokenv,tokenc); 
                                        execvp(tokenv[0],tokenv);
                                        perror(tokenv[0]);
                                        close(fd[1]);

                                        break;

                	default:        close(1);
                                        dup(fd[0]);
                                        execvp(tokenv[0],tokenv);
                                        perror(tokenv[0]);
                                        close(fd[0]);

                                        break;
                }
 
      	} 
}
