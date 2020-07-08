/* util.c */
#include <stdio.h>

/* purpose: abort a program
 * input:   a stings to print
 * output:  nothing (size effect: program exits)
 */
abort(s) char *s;
{
  printf("%s\n", s);
  exit(-1);
}

/* purpose: allocate memory
 * input:   the number of bytes to allocate
 * output:  a pointer to the memory (program aborts if no memory is available)
 */
char *check_malloc(size) int size;
{
  char *cp, *malloc();

  cp = malloc(size);
  if (cp == NULL)
    abort("No Core");

  return (cp);
}

/* purpose: copy a string
 * input:   a string, s
 * output:  a copy of s in newly allocated memory
 */
char *string_copy(s) char *s;
{
  char *s_copy;

  s_copy = (char *)check_malloc(strlen(s) + 1);
  strcpy(s_copy, s);
  return (s_copy);
}
