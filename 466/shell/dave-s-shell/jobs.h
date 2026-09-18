/* jobs.h */

static const int MAX_PROCESSES = 5;

typedef struct {
  int pid;
  char *name;
} tJob;

void run(char **tokenv, tJob background_processes[]);
