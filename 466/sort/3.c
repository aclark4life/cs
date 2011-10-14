#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>

main()
{
	int a[2],b[2],pid,i;
    	FILE *infile,*outfile,*temp;
  	char **tokenv=(char **)malloc(sizeof(char *));
  	char **token=(char **)malloc(sizeof(char *));
	char *s;
	char *buf=(char *)malloc(sizeof(char));


       	infile = fopen("infile","r");
	outfile=fopen("outfile","ab");
	temp=fopen("temp","ab");
	tokenv[0]="sort";  
	token[0]="cat";  
	pipe(a);
	pipe(b);
	pid=fork();
	switch(pid)
	{
		case 0:	        close(0);  /* close stdin */
				dup(a[0]); /* 'execvp sort' to the pipe instead of stdin */
			        close(1);  /* close stdout */
				dup(b[0]); /* send the result of sort to the pipe instead of stdout */
				/*close(a[0]);*/
				execvp(tokenv[0],tokenv); /* exec sort */
				break;	
		default:	close(1); /* close stdout */
				dup(a[1]); /* printf to the pipe instead of stdout */
				/*close(a[1]);*/
				for(i=0;(s=fread_long(infile))!=NULL;i++)
				{
					if (strlen(s) >= 50)
					{
						tokenv = realloc(tokenv,sizeof(char*)*(i+2));
						tokenv[i]=s;
						write(1,tokenv[i],strlen(s));
					}
					
				}
				close(0); /* close stdin */
				dup(b[1]); /* pipe takes the place of stdin */
			execvp(token[0],tokenv);  /* exec 'cat' on sorted data to prove pipe works */

   			/*	for ( buf=read_long(); buf!=NULL; s=read_long() ){
					printf("%s\n",buf);
				} */

		/*		read(b[1],buf,strlen(s));
				printf("%s\n",buf);
				*/



				/* cheating ? */
				/*
				system("head -n 10 temp >> outfile");
				system("/usr/xpg4/bin/tail -n 10 temp >> outfile");
				fprintf(outfile,"Happy Birthday!\n");
				*/

				break; 

	}
}



