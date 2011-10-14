/* token_ring.c : setup a token ring and hold elections when token is lost */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_PROCESSES 10
#define PORT_BASE 5200
#define TRUE 1
#define FALSE 0


typedef int tSocket;
typedef union
{
    char as_char[2];
    short as_short;
} tToken;
#define TOKEN_SIZE (sizeof (tToken))
#define NO_TOKEN   ((tToken)(short) -1)

#define send_token(s, t) {tToken _t = t; write(s, &_t, TOKEN_SIZE);} 

tToken create_new_token();
tToken receive_any ();

main(int argc, char *argv[])
{
    tSocket others[MAX_PROCESSES]; 
    int my_number, max_processes, next;

    if (argc < 3)
    {
	printf("usage: %s <my #> <max # of processes> <process host list>\n");
    }
    my_number = atoi(argv[1]);
    max_processes = atoi(argv[2]);
    next = (my_number+1) % max_processes ;   /* static order */

    setup(others, my_number, max_processes, &argv[3]);

    if (my_number == 0)			     /* initial token */
        send_token(others[next], create_new_token());

    run(others, my_number, next);            /* 'never' returns */	
}


run (tSocket others[], int my_number, int next)
{
/* you don't have to use these */
    long last_have_time, king_declare_time;
    int could_be_king, election;
    tToken token;


    last_have_time = time((time_t *) 0);
    election = FALSE;

    while (TRUE)
    {
        token = receive_any(others, my_number);

        if (0 && token.as_short != -1 )   /* for debugging */
            printf("token %d %d  (%d)\n", token.as_char[0], 
	           token.as_char[1], token.as_short);

        switch (token.as_char[0])
	{
	    ...
	}
    } 
}


setup(tSocket others[], int my_number, int max_processes, char *hosts[])
{
    int i;

    srandom(getpid());

    for (i=0; i< MAX_PROCESSES; i++)
	others[i] = NULL;

    others[my_number] = create_socket(PORT_BASE+my_number);
    if (others[my_number] < 0)
    {
	perror("create socket");
	exit(1);
    }


    for(i=0; i<max_processes; i++)
    {
	if (i == my_number)
	{
	    int j;
	    short from;
	    tSocket s;

	    for(j=i; j<max_processes-1; j++)
	    {
                s = wait_for_connection(others[my_number]);
	        read(s, &from, sizeof(short));
	        printf("connect %d %d\n", my_number, from);
	        others[from] = s;
		fcntl(others[from], F_SETFL, O_NDELAY);
	    }
	}
	else if (i < my_number)
	{
	    short num;

	    others[i] = open_socket(hosts[i], PORT_BASE+i);
	    if (others[i] < 0)
	    {
		char msg[50];
		sprintf(msg,"ABORT! can't open socket to %d returned %d", i, others[i]);
		perror(msg);
		exit(-1);
	    }
	    num = my_number;
	    write(others[i], &num, sizeof(short));
	    fcntl(others[i], F_SETFL, O_NDELAY);
	}
    }
}


tToken create_new_token()
{
}


tToken receive_any (tSocket others[], int my_number)
{
}


declare_me_king(int me, tSocket others[])
{
}
