#include<stdio.h>
#define BUF_SIZE 2

main()
{
	int a[2],b[2],pid,i;
    	FILE *infile, *fin;
  	char **stringv=(char **)malloc(sizeof(char *)); 
	char *string=(char *)malloc(sizeof(char));
	char *buf=(char *)malloc(sizeof(char)*BUF_SIZE); 
	char **programv=(char **)malloc(sizeof(char *)*2);

       	infile = fopen("infile","r");
	pipe(a);
	pipe(b);
	programv[0]="sort";
	programv[1]=NULL;
	pid=fork();
	switch(pid)
	{
		case 0:		close(0);  
				dup(a[0]);  /* to sort */

   				close(a[0]);/* ? */
            			close(a[1]);/* ? */

            			close(b[0]);/* ? */
            			close(b[1]);/* ? */

			        /*close(1);   */
				dup(b[1]);  /* from sort */
				

				/*write(1,"hello",5);*/
			      	/*execvp(programv[0],programv); */  /* exec sort */
				execlp("sort", "sort", (char *) 0);

				break;
		default:	/*close(1);
				dup(a[1]);

				close(0); 
				dup(b[0]);
				*/	

				for(i=0;(string=fread_long(infile))!=NULL;i++)  
				{
				  	if (strlen(string) >= 50)
					{
				  		stringv = realloc(stringv,sizeof(char*)*(i+2));
						stringv[i]=string;
					 	write(a[1],stringv[i],strlen(string));   
					}
				}
				fclose(infile);
				close(a[1]); /* this one is important */

/*				fin=fdopen(b[0],"r");
            			for(i=0; i<10; i++)
            			{
                			if (fgets(buf, BUF_SIZE, fin) == NULL)
                    			printf("fgets returned NULL!\n");
                			printf("%s", buf);
            			}
            			fclose(fin);
				*/

			/*	read(0,buf,BUF_SIZE);   
				write(2,buf,BUF_SIZE); 
				*/
				
				break; 
	}
}
