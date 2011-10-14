#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>

main()
{
	int a[2];
	int pid,fd,i;
  	char **tokenv=(char **)malloc(sizeof(char *));
	char *buf=(char *)malloc(sizeof(char));
    	FILE *infile; 

       	infile = fopen("main.c","r");

	for(i=0;i < 50; i++) buf[i]=NULL; 

	tokenv[0]="sort";  
	pipe(a);

	pid=fork();
	switch(pid)
	{
		case 0:		/*execvp(tokenv[0],tokenv);*/
				break;	
		default: 	fgets(buf,50,infile);
				write(1,buf,50);
				break;
	}
}



