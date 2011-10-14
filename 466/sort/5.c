#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>
#define BUF_SIZE 1000 

main()
{
	int a[2],b[2],pid,i;
    	FILE *infile;
  	char **stringv=(char **)malloc(sizeof(char *)); 
	char *string=(char *)malloc(sizeof(char));
	char *buf=(char *)malloc(sizeof(char)*BUF_SIZE); 
	char **programv=(char **)malloc(sizeof(char *)*2);

       	infile = fopen("infile","r");
	pipe(a);
	pipe(b);
	programv[0]="cat";
	programv[1]=NULL;
	pid=fork();
	switch(pid)
	{
		case 0:	        close(0);   /*close stdin */
				dup(a[0]);  /*0 == pipe (a[0]) instead of stdin */
			        close(1); /*close stdout */
				dup(b[1]); /* 1 == pipe (b[1]) instead of stdout */
			        execvp(programv[0],programv); /* exec sort */

				break;
		default:	close(1);  /*close stdout*/
				dup(a[1]);/*write to pipe instead of stdout*/

				for(i=0;(string=fread_long(infile))!=NULL;i++)  
				{
				  	if (strlen(string) >= 50)
					{
				  		stringv = realloc(stringv,sizeof(char*)*(i+2));
						stringv[i]=string;
						write(1,stringv[i],strlen(string));   
					}
				}
				
				close(0);  /*close stdin*/
				dup(b[0]); /*0 == pipe instead of stdin*/
				read(0,buf,BUF_SIZE);  
				write(2,buf,BUF_SIZE);
			
				
				break; 
	}
}
