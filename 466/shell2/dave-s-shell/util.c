/* utils.c */

static char *cr = "copyright (c) David Binkley 1993";

#include "strings.h"
#include <stdio.h>

int die(char *s) {
  printf("%s\n", s);
  exit(-1);
}

char *check_malloc(size) int size;
{
  char *cp, *malloc();
  /*printf("check malloc allocating %d bytes\n", size) ;*/

  cp = malloc(size);
  if (cp == NULL)
    die("check_malloc: No Core");

  return (cp);
}

void *check_realloc(void *p, int size) {
  p = (void *)realloc(p, size);
  if (p == NULL)
    die("check_realloc: No Core");
  return (p);
}

char *string_copy(s) char *s;
{
  char *s_copy;

  s_copy = (char *)check_malloc(strlen(s) + 1);
  strcpy(s_copy, s);
  return (s_copy);
}

/* purpose: read a string of indeterminate length
 * input:  nothing
 * output: string read
 */
char *read_long() {
  char c, *buff;
  int len;

  buff = check_malloc(1);
  *buff = '\0';

  for (len = 0; ((c = getchar()) != EOF); len++) {
    if (c == '\n') {
      buff[len] = '\0';
      return (buff);
    }
    buff = check_realloc(buff, len + 1);

    buff[len] = c;
  }

  if (len == 0) {
    free(buff);
    return (NULL);
  } else
    return (buff);
}

/* purpose: parse string into argument vector
 * input:   the string to parse, str
 * output:  a argument vector (array of pointers to the non-white space
 *	    strings in str)
 */
char **tokenize(char *str) {
  char **tokens, *tmp;
  int tc;

  tokens = (char **)check_malloc(sizeof(char *));
  if (tokens == NULL)
    die("No Core");
  *tokens = NULL;

  for (tmp = strtok(str, " \t"), tc = 0; tmp; tmp = strtok(NULL, " \t"), tc++) {
    tokens =
        (char **)check_realloc(tokens, (tc + 2) * sizeof(char *)); /* why +2 */
    tokens[tc] = tmp;
  }

  tokens[tc] = NULL;
  return (tokens);
}
