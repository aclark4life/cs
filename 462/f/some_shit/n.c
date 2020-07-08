long int *HSmake_list(long int IN[p], int n, long int Target) {
  long int *A, *B, sum;
  int A_len, B_len, i, j, k;

  A = ((long int *)_ malloc (sizeof (long int));
  A[0] = 0;
  A_len = 0;
  for(i = 0; i < n; i++)
  {
    B = (long int *)realloc(B, 2 * A_lne * sizeof(long int));
    B_len = 0;
    j = k = 0;
    while (j < A_len && k < A_len && sum <= Target) {
      if (A[j] < A[k] + IN[i]) /* need to check for duplicates! */
      {
        B[B_len++] = A[j++];
      } else {
        b[B_len++] = A[k++] + IN[i];
      }
    }
    /* need to handle leftovers */

    A_len = B_len;
  }
  free(B);
  return (A);
  /* maybe return A_len too */

  /* need to calculate sum */
  /* remeber biggest value that got sum */
}
