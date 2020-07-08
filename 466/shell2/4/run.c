/* run.c */
/* note: does no error checking for "foo < i < j", "foo >d >g", etc. */

#include "jobs.h"
#include "util.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

static char **check_handle_pipe(char **tokenv);
static int is_background_job(char **tokenv);
static void kill_job(int job, tJob background_processes[]);
static void print_jobs(tJob background_processes[]);
static void record_background_job(char *job_name, tJob background_processes[],
                                  int pid);
static void note_finished_jobs(tJob background_processes[], int pid);
static void shift_tokenv_by_2(char **tokenv);
static void check_redirect_stdin(char **tokenv);
static void check_redirect_stdout(char **tokenv);
static void external_command(char **tokenv, tJob background_processes[]);
