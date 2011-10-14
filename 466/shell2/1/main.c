#include<stdio.h>

extern void prompt();
extern char *read_long();
extern char **tokenize(char *,int*);
extern int no_token(char **);
extern int check_for_exit(char **);
extern void do_fork(char **,int *);

main()
{
	char **tokenv;
	char *s;
	int tokenc;
	int i;

	prompt();
	for ( s=read_long(); s!=NULL; s=read_long() )
	{
		tokenv=tokenize(s,&tokenc);
		if (!no_token(tokenv)) /* if there is a token */
		{
			check_for_exit(tokenv); 
			do_fork(tokenv,&tokenc);
		}
		prompt();
	}
}



