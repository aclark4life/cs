#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  int i, n = 0;
  int *a;
  float mean, stdev, sum = 0, sum_sq_diff = 0;

  if (argc < 2 || argc > 3) {
    printf("\nUsage: %s num_int_to_avg [filename]\n", argv[0]);
    printf("E.g.\n%s 3\nEnter 3 integers for me to average:\n1 3 3\n", argv[0]);
    printf("Mean: 2.333333\nStandard Deviation: 1.154701\n");
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);
  if (n <= 0) {
    printf("Number of integers must be positive.\n");
    exit(EXIT_FAILURE);
  }

  a = (int *)malloc(n * sizeof(int));
  if (a == NULL) {
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      printf("Unable to open the input file.\n");
      free(a);
      exit(EXIT_FAILURE);
    }
  } else {
    file = stdin;
    printf("Enter %d integers for me to average:\n", n);
  }

  for (i = 0; i < n; i++) {
    if (fscanf(file, "%d", &a[i]) != 1) {
      printf("Failed to read integer.\n");
      free(a);
      if (file != stdin)
        fclose(file);
      exit(EXIT_FAILURE);
    }
  }

  if (file != stdin)
    fclose(file);

  for (i = 0; i < n; i++) {
    sum += a[i];
  }
  mean = sum / n;

  for (i = 0; i < n; i++) {
    sum_sq_diff += pow(a[i] - mean, 2);
  }
  stdev = sqrt(sum_sq_diff / (n - 1));

  free(a);

  printf("Mean: %f\n", mean);
  printf("Standard Deviation: %f\n", stdev);

  return 0;
}
