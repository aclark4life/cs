#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_tokens(char **tokenv, int *tokenc) {
  int pid;
  int status;

  pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    break;

  case 0:
    /* Inside child: start the pipeline execution */
    /* This will handle pipes, <, and > recursively */
    handle_pipe(tokenv, tokenc);
    /* handle_pipe calls exit() so we shouldn't reach here */
    exit(EXIT_FAILURE);

  default:
    /* Inside parent: wait for the command/pipeline to finish */
    if (wait(&status) == -1) {
      perror("wait");
    }
    break;
  }
}
