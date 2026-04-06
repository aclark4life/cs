#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#define PROMPT "* "

int main(void) {
  char **tokenv;
  char *s;
  int tokenc;

  s = prompt();
  while (s != NULL) {
    tokenv = tokenize(s, &tokenc);
    if (tokenv[0] != NULL) {
      dump_tokens(tokenv, &tokenc);
      handle_tokens(tokenv, &tokenc);
    }
    free(tokenv);
    free(s);
    s = prompt();
  }

  return EXIT_SUCCESS;
}
