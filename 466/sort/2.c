#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>

main()
{
	int a[2];
	int pid,i;
  	char **tokenv=(char **)malloc(sizeof(char *));
    	FILE *infile; 
	char *s;

       	infile = fopen("test","r");
	tokenv[0]="sort";  
	pipe(a);

	pid=fork();
	switch(pid)
	{
		case 0:	        close(0);  /* close stdin */
				dup(a[0]); /* 'execvp sort' to the pipe instead of stdin */
				close(a[0]); 
				execvp(tokenv[0],tokenv); /* exec sort */
				break;	
		default:	close(1); /* close stdout */
				dup(a[1]); /* printf to the pipe instead of stdout */
				close(a[1]);
				for(i=0;(s=fread_long(infile))!=NULL;i++)
				/* while ((s=fread_long(infile))!=NULL) */
				{
					if (strlen(s) >= 50)
					{
						tokenv = realloc(tokenv,sizeof(char*)*(i+2));
						tokenv[i]=s;
						printf("%s\n",s);
					}
					
				}
			/*
				for(i=0;(s=fread_long(infile))!=NULL;i++)
				{
					if (strlen(s) >= 50)
					{
						tokenv[i]=s;
						tokenv = realloc(tokenv,sizeof(char*)*(i+2));
						printf("%s\n",s);
					}
				}
			*/
				


				break;
	}
}



