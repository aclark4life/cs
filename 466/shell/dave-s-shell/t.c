/* main */

#include "jobs.h"

#include <stdio.h>
#include <stdlib.h>

extern char *read_long(void);
extern char **tokenize(char *);
static char *prompt(void);

int main(void) {
  char *input;
  char **tokenv;
  int i;
  tJob background_processes[MAX_PROCESSES + 1];

  for (i = 0; i < MAX_PROCESSES; i++)
    background_processes[i].pid = 0;
  background_processes[MAX_PROCESSES].pid = -1;

  input = prompt();
  while (input != NULL) {
    tokenv = tokenize(input);

    if (tokenv[0] != NULL)
      run(tokenv, background_processes);

    free(tokenv);
    free(input);
    input = prompt();
  }

  return EXIT_SUCCESS;
}

static char *prompt(void) {
  printf("command:");
  return (read_long());
}
