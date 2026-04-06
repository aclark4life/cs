#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_pipeline(char **tokenv, int tokenc) {
  int i;
  int pipe_pos = -1;

  for (i = 0; i < tokenc; i++) {
    if (strcmp(tokenv[i], "|") == 0) {
      pipe_pos = i;
      break;
    }
  }

  if (pipe_pos == -1) {
    /* No pipe, handle redirection and execute directly */
    handle_less_than(tokenv, &tokenc);
    handle_greater_than(tokenv, &tokenc);
    execvp(tokenv[0], tokenv);
    perror(tokenv[0]);
    exit(EXIT_FAILURE);
  }

  /* Pipe found at pipe_pos */
  tokenv[pipe_pos] = NULL; /* Null terminate first command */

  int fd[2];
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    /* Child: execute left side */
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    handle_less_than(tokenv, &pipe_pos);
    handle_greater_than(tokenv, &pipe_pos);
    execvp(tokenv[0], tokenv);
    perror(tokenv[0]);
    exit(EXIT_FAILURE);
  } else {
    /* Parent: execute right side */
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);

    execute_pipeline(tokenv + pipe_pos + 1, tokenc - pipe_pos - 1);
  }
}

void handle_pipe(char **tokenv, int *tokenc) {
  /* This function is now just a wrapper for the recursive pipeline executor */
  execute_pipeline(tokenv, *tokenc);
}
