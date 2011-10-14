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
  	char **prog=(char **)malloc(sizeof(char *)*2);
	char *s;

/*	char buf[1];  */

	char *buf=(char *)malloc(sizeof(char)); 
/*	char *q=(char *)malloc(sizeof(char)*1024); */

	int count;
/*	*buf='\0'; */
       	infile = fopen("infile","r");
	prog[0]="cat";  
	prog[1]=NULL;
	/*for(i=0;i < 1; i++) buf[i]=NULL;   */

	pipe(a);
	pipe(b);
	pid=fork();
	switch(pid)
	{
		case 0:	        close(0);   /*close stdin */
				dup(a[0]);  /*0 == pipe instead of stdin */

			        close(1);  /*close stdout */
				dup(b[1]); /* 1 == pipe instead of stdout */

			/*	write(1,"hello",5);   */
				execvp(prog[0],prog); /* exec sort */ 

				break;	
		default:	close(1);  /*close stdout*/
				dup(a[1]);/*write to pipe instead of stdout*/

				for(i=0;(s=fread_long(infile))!=NULL;i++)
				{
				/*	if (strlen(s) >= 50)
					{
						tokenv = realloc(tokenv,sizeof(char*)*(i+2));
						tokenv[i]=s;
						write(1,tokenv[i],strlen(s));
					}
					*/
						write(1,tokenv[i],2);
				}
				close(0); /*close stdin*/
				dup(b[0]);/*read from pipe instead of stdin*/


				read(0,buf,5);  
				write(2,buf,5);

		 	/*	for(; ( count = read(0,q,1024) ) != 0 ;  ) 
				{
					int buflen=strlen(buf);
					fprintf(stderr,"q=%s\n",q);
					buf=(char*)realloc (buf,sizeof(char)*(buflen+count+1));
					strncat(buf+buflen,q,count);
					buf[buflen+count]='\0';

				}
				*/
				break; 

	}
}
