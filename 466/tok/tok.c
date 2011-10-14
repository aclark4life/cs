/* token_ring.c : setup a token ring and hold elections when token is lost */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

#define MAX_PROCESSES 10
#define PORT_BASE 5200
#define TRUE 1
#define FALSE 0

typedef int tSocket;

typedef union
{
    char as_char[2];
    short as_short;
} tToken;  /* tToken == 16 bits */

#define TOKEN_SIZE (sizeof (tToken))
#define NO_TOKEN ((tToken)(short) -1)
#define send_token(s, t) {tToken _t = t; write(s, &_t, TOKEN_SIZE);} 

tToken create_new_token(char,int);
tToken receive_any ();

main(int argc, char *argv[])
{
    tSocket others[MAX_PROCESSES]; 
    int my_number, max_processes, next;
    tToken token;
    int port_adjuster;

    if (argc < 5)
    {
	printf("usage: %s <my #> <max # of processes> <port adjuster> <process host list>\n",argv[0]);
	printf("	port adjuster			This allows the user to \n");
	printf("					change the port value. \n");
	printf("				       	Enter a number and it will \n "); 
	printf("				        be added to the PORT_BASE of \n");
	printf("				        of 5200. YOU MUST ENTER A VALUE\n");
	printf("				        FOR THE PORT ADJUSTER!\n");
	exit(0);
    }

    my_number = atoi(argv[1]);
    max_processes = atoi(argv[2]);
    next = (my_number+1) % max_processes ;   /* static order */
    port_adjuster = atoi(argv[3]); /* this is for my  'port adjuster' that allows you to change
					the port number 'on the fly'. */

    setup(others, my_number, max_processes, &argv[4]);  
    if (my_number == 0)
    { 			     /* initial token */
        send_token(others[next],create_new_token('a',my_number));  
    }
    run(others, my_number, next, max_processes);      /* 'never' returns */	  
}

run (tSocket others[], int my_number, int next, int max_processes)
{
    int election;
    tToken token;
    int i;

    election = FALSE;

    while (TRUE)
    {
        token = receive_any(others, my_number, max_processes);
	/* for debugging */
/*        if (token.as_short != -1 )  
		printf("token %c %d\n", token.as_char[0], token.as_char[1]);  
		*/

            	/*printf("token %c %c (%d)\n", token.as_char[0], token.as_char[1], token.as_short); */

        switch (token.as_char[0])
	{
		case 'a':       if((random() % 100) != 10)
				{
					send_token(others[next],token);
				}
				else
				{
					printf("oops, i dropped the token. \n");
				}
				break;



		case 'e': 	election=TRUE;	
				printf("start election.\n");

				/*if(token.as_short==-1)	
				{
					election=FALSE;
					printf("i win. ");
					printf("%d is sending election token to %d\n",my_number,next); 
					send_token(others[next],create_new_token('a',my_number));
				}
				*/

				if(token.as_char[1]>my_number)
				{
					printf("i lose\n");
					election=FALSE;	
				}
				else if(token.as_char[1]<my_number)
				{
					/*printf("i win: ");*/
					printf("im sending %d an election token with my_number=%d\n",next,my_number);
					send_token(others[token.as_char[1]],create_new_token('e',my_number)); 
				}

				break;


		default:	printf("Hey where the hell is the token?\n");
				printf("start election.\n");
			/*	election=TRUE; */
				for(i=next;i<max_processes;i++)
				{
					if(i != my_number)
					{
						printf("im sending %d an election token with my_number=%d\n",i,my_number);
						send_token(others[i],create_new_token('e',my_number));
					}
				}
				while(election==TRUE)
				{
					token=receive_any(others, my_number, max_processes);

					if(election==TRUE)
					{
						election=FALSE;
						printf("i win. ");
						/*printf("%d is sending election token to %d\n",my_number,next);  */

						printf("%d is sending a token to %d\n",my_number,next);  
						send_token(others[next],create_new_token('a',my_number));
					}
				}	
				break;




				/*	else if(token.as_char[1]>my_number)
					{
						printf("i lose\n");
						election=FALSE;	
						break;

					}
					else if(token.as_char[1]<my_number)
					{
						printf("im sending %d an election token with my_number=%d\n",next,my_number);
						send_token(others[token.as_char[1]],create_new_token('e',my_number));
					}
					break;
					*/

	}
    } 
}

setup(tSocket others[], int my_number, int max_processes, char *hosts[],int port_adjuster)
{
    int i;

    srandom(getpid());

    for (i=0; i< MAX_PROCESSES; i++)
	others[i] = NULL;

    others[my_number] = create_socket(PORT_BASE+my_number+port_adjuster);

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
	    others[i] = open_socket(hosts[i], PORT_BASE+i+port_adjuster);
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


tToken create_new_token(char c,int my_number)
{
	tToken token;

	token.as_char[0]=c; 
	token.as_char[1]=my_number; 

	return token;
}


tToken receive_any (tSocket others[], int my_number, int max_processes)
{ 	/* check to see if anyone is sending me a token */
	tToken token;
	long start,stop;
	int i;
	
	token.as_short = -1;

/*	t=time((time_t *)0);  */
/*      while ( time((time_t *)0) - t < 15) */
/*	printf("im here\n"); */
	for(start=time((time_t *)0),stop=time((time_t *)0);stop-start < 3;stop=time((time_t *)0))
	{

		for(i=0;i<max_processes;i++)
		{
			if (i!= my_number)
			{
 				read(others[i],&token,TOKEN_SIZE);  
				if (token.as_short != -1)
				{
					printf("Got one! %c %d\n",token.as_char[0],token.as_char[1]); 
					return token;
				}
			}
		}
	}
	return token;

}

declare_me_king(int me, tSocket others[])
{
	/*tell everyone that i want to be king*/
}
