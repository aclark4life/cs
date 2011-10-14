#include "stdio.h"

main()
{
    int Sort[2];

    if (pipe(Sort) == -1)
	perror("pipe1");

    switch( fork() )
    {
	case -1 : perror("fork"); exit(-1); break;
	case 0 : 
	{
	    if (close (0) == -1)
		perror("close 1");
	    if (dup(Sort[0]) != 0)
		perror("dup1");

	    close (1);
	    dup(Sort[0]);
	
            close(Sort[0]);
            close(Sort[1]);

	    execlp("sort", "sort", (char *) 0);
	    perror("execvp!");
	}


	default:
	{
	    FILE *f, *fin;
	    char buf[255];
	    int i;

	    close(Sort[0]);

	    f = fopen ("foo", "r");
	    if (f == NULL)
	    {
		printf("can't open foo");
		exit(-1);
	    }
            while(fgets(buf, 100, f) != NULL)
	    {
		if (strlen(buf) > 50)
		    write(Sort[1], buf, strlen(buf));
	    }
	    fclose(f);

            /*close(Sort[1]);  /* this ones improtant */
	    /* done writing, close stuff then read results */

            fin = fdopen(Sort[1], "r");
            for(i=0; i<10; i++)
	    {
		if (fgets(buf, 100, fin) == NULL)
		    printf("fgets returned NULL!\n");
		printf("%s", buf);
	    }
	    fclose(fin);
	}
    }
}

