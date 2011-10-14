#include "stdio.h"

main()
{
    int toSort[2], fromSort[2];

    if (pipe(toSort) == -1)
	perror("pipe1");
    if (pipe(fromSort) == -1 )
	perror("pipe2");

    switch( fork() )
    {
	case -1 : perror("fork"); exit(-1); break;
	case 0 : 
	{
	    if (close (0) == -1)
		perror("close 1");
	    if (dup(toSort[0]) != 0)
		perror("dup1");

	    close (1); 
	    dup(fromSort[1]);
	    
	    

            close(toSort[0]);
            close(toSort[1]);

            close(fromSort[0]);
            close(fromSort[1]);

	    /*execvp("/bin/date", "date", (char *) 0);*/
	    execlp("sort", "sort", (char *) 0);
	    perror("execvp!");
	}


	default:
	{
	    FILE *f, *fin;
	    char buf[255];
	    int i;

	    close(toSort[0]);
            close(fromSort[1]);

	    f = fopen ("infile", "r");
	    if (f == NULL)
	    {
		printf("can't open foo");
		exit(-1);
	    }
            while(fgets(buf, 100, f) != NULL)
	    {
		if (strlen(buf) > 50)
		    write(toSort[1], buf, strlen(buf));
	    }
	    fclose(f);

            close(toSort[1]);  /* this ones improtant */
	    /* done writing, close stuff then read results */

            fin = fdopen(fromSort[0], "r");
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

