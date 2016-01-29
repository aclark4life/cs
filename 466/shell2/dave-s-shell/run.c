/* run.c */
/* note: does no error checking for "foo < i < j", "foo >d >g", etc. */

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "util.h"
#include "jobs.h"

static char **check_handle_pipe(char **tokenv);
static int  is_background_job(char **tokenv);
static void kill_job(int job, tJob background_processes[]);
static void print_jobs(tJob background_processes[]);
static void record_background_job(char *job_name, 
				  tJob background_processes[], int pid);
static void note_finished_jobs(tJob background_processes[], int pid);
static void shift_tokenv_by_2(char **tokenv);
static void check_redirect_stdin(char **tokenv);
static void check_redirect_stdout(char **tokenv);
static void external_command(char **tokenv, tJob background_processes[]);


static dump_tokens(char **t)
{
    fprintf(stderr, "tokens: ");
    while (*t)
        fprintf(stderr,"  '%s' ", *t++);
    fprintf(stderr, "\n");
}


void run(char **tokenv, tJob background_processes[])
{
    if (strcmp(tokenv[0], "jobs") == 0)
    {
        print_jobs(background_processes);
        note_finished_jobs(background_processes,0);
    }
    else if (strcmp(tokenv[0], "kill") == 0)
    {
	if isdigit((*tokenv[1]))
            kill_job(atoi(tokenv[1]), background_processes);
	else
	    printf("usage: kill <job number>\n");
        note_finished_jobs(background_processes,0);
    }
    else
    {
        external_command(tokenv, background_processes);
    }
}


static void print_jobs(tJob background_processes[])
{
    int i;

    for(i=0; background_processes[i].pid != -1; i++)
    {
        if (background_processes[i].pid != 0)
        {
            printf("%d %d %s\n", i, background_processes[i].pid,
                                 background_processes[i].name);
        }
    }
}


static void kill_job(int job, tJob background_processes[])
{
    if (job < 0 || job >= MAX_PROCESSES || background_processes[job].pid == 0)
	printf("invalid job number\n");
    else
    {
        if (kill(background_processes[job].pid, SIGTERM) == -1)
	    perror("kill");
        background_processes[job].pid = 0;
    }
}


static void external_command(char **tokenv, tJob background_processes[])
{
    int pid;
    int back_ground = is_background_job(tokenv);  /* removes '&' */
    
    if (tokenv[0] == NULL)			  /* input = "& " */
	return;

    pid = fork();
    if (pid < 0)
        die ("fork error");

    if (pid == 0)                        /* child */
    {
	check_redirect_stdin(tokenv);
	check_redirect_stdout(tokenv);
        if (tokenv[0] == NULL)			  /* input = "> f   or  < f" */
	    exit(0);

	tokenv = check_handle_pipe(tokenv);
        if (tokenv[0] == NULL)			  /* input = "> f   or  < f" */
	    exit(0);

        execvp(tokenv[0], tokenv);
	perror("execvp");
        printf("can't run %s\n", tokenv[0]);
        die("bye");
    }
    else
    {
	if (back_ground)
	{
            record_background_job(tokenv[0], background_processes, pid);
	    note_finished_jobs(background_processes,0);
	}
	else
	{
	    note_finished_jobs(background_processes,pid);
	}
    }
}


static int is_background_job(char **tokenv)
{
    int i;

    for(i=0; tokenv[i] != NULL; i++)   /* assumes & is last */
    {
        if (strcmp("&", tokenv[i]) == 0)
	{
	    tokenv[i] = NULL;
	    return (TRUE);
	}
    }

    return(FALSE);
}


static void record_background_job(char *job_name,   
				  tJob background_processes[], 
				  int pid)
{
    int i;
    for(i=0; background_processes[i].pid != -1; i++)
    {
        if (background_processes[i].pid == 0)
        {
            background_processes[i].pid = pid;
            background_processes[i].name = string_copy(job_name);
            break;
        }
    }

    if (background_processes[i].pid == -1)
        printf("process table overflow.  Have fun.\n");
}


/* record jobs that finish, wait for pid to finish if pid != 0  */
static void note_finished_jobs(tJob background_processes[], int pid)
{
    int child_pid;

    do
    {
        child_pid = wait3(0, WNOHANG, 0);

	if (child_pid == -1)  /* no unwaited for childred */
	    break;

	if (child_pid != 0) 
	{
            int i;

            for(i=0; background_processes[i].pid != -1; i++)
            {
                if (background_processes[i].pid == child_pid)
                {
                    background_processes[i].pid = 0;
                    break;
                }
            }
	    printf("--- child %d exited\n", child_pid);
	}
    } while (pid != child_pid);
}


static void shift_tokenv_by_2(char **tokenv)
{
    while(*tokenv = *(tokenv + 2))
	tokenv++;
}


static void check_redirect_stdin(char **tokenv)
{
    int i;

    for(i=0; tokenv[i] != NULL; i++)  
    {
        if (strcmp("<", tokenv[i]) == 0)
	{
	    close(0);
	    if (open(tokenv[i+1], O_RDONLY) != 0)
	      die("open input");
	    shift_tokenv_by_2(&tokenv[i]);
	}
    }
}


static void check_redirect_stdout(char **tokenv)
{
    int i;

    for(i=0; tokenv[i] != NULL; i++)  
    {
        if (strcmp(">", tokenv[i]) == 0)
	{
	    close(1);
	    if (open(tokenv[i+1], O_CREAT | O_WRONLY, 0666) != 1)
	      die("open output");

	    shift_tokenv_by_2(&tokenv[i]);
	}
    }
}


static char **check_handle_pipe(char **tokenv)
{
    int i;

    for(i=0; tokenv[i] != NULL; i++)   /* assumes & is last */
    {
        if (strcmp("|", tokenv[i]) == 0)
	{
	    int fds[2];
	    tokenv[i] = NULL;

	    if (pipe(fds))
		die("pipe");

            switch (fork())
	    {
		case -1: die("fork");
		case 0:
		    close(1);
		    if (dup(fds[1]) != 1)
			die("dup");
		    close(fds[0]);
		    close(fds[1]);
		    return (tokenv);

		default:
		    close(0);
		    if (dup(fds[0]) != 0)
			die("dup");
		    close(fds[0]);
		    close(fds[1]);
		    return (check_handle_pipe(&tokenv[i+1]));
	    }
	}
    }
    return (tokenv);
}


