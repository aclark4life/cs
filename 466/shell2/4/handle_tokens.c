#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_tokens(char **tokenv, int *tokenc) {
  int pid;
  int huh;

  pid = fork();
  switch (pid) {
  case 0:
    handle_greater_than(tokenv, *tokenc);
    /*
                    handle_less_than(tokenv);
                    tokenv=handle_pipe(tokenv);
                    */
    execvp(tokenv[0], tokenv);
    perror(tokenv[0]);
    exit(0);

    break;

  default:
    if (wait(&huh) == -1) {
      perror(tokenv[0]);
    }
    break;
  }
}
