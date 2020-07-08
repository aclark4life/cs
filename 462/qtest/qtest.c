// qtest - a program to time the standard C function qsort.
// initial code courtesy of the qsort man page.
// assistance with additional code from nick russo.
//
// - alex clark

static int intcompare(int *i, int *j) {
  if (*i > *j)
    return (1);
  if (*i < *j)
    return (-1);
  return (0);
}
void main(int argc, char *argv[]) {

  int *a;

  long n = atol(argv[1]);

  printf("%ld\n", n);

  a = malloc

  /*	qsort((char *) a,  10, sizeof(int), intcompare ) ;
          for ( i = 0 ; i < 10 ; i ++ ) printf ( "%d", a[i] ) ;
          printf ("\n");
  */
}
