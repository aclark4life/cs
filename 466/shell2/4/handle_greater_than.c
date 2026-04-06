#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PERMISSIONS 0644

void handle_greater_than(char **tokenv, int *tokenc) {
  int i;
  for (i = 0; i < *tokenc; i++) {
    if (strcmp(tokenv[i], ">") == 0) {
      if (tokenv[i + 1] == NULL) {
        fprintf(stderr, "Error: No output file specified after '>'\n");
        return;
      }
      int fd = open(tokenv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
      if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
      }
      if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
      }
      close(fd);

      /* Remove '>' and the filename from tokenv */
      free(tokenv[i]);
      free(tokenv[i + 1]);
      int j;
      for (j = i; j < *tokenc - 1; j++) {
        tokenv[j] = tokenv[j + 2];
      }
      *tokenc -= 2;
      tokenv[*tokenc] = NULL;
      i--;
    }
  }
}
