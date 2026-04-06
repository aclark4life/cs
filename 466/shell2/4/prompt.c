#include "shell.h"
#include <stdio.h>
#define PROMPT "* "

extern char *read_long(void);

char *prompt(void) {
  printf(PROMPT);
  return (read_long());
}
