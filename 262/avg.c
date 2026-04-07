#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  int i, num_values = 0;
  int *values;
  float mean, stdev, sum = 0, sum_sq_diff = 0;

  if (argc < 2 || argc > 3) {
    printf("\nUsage: %s num_int_to_avg [filename]\n", argv[0]);
    printf("E.g.\n%s 3\nEnter 3 integers for me to average:\n1 3 3\n", argv[0]);
    printf("Mean: 2.333333\nStandard Deviation: 1.154701\n");
    exit(EXIT_FAILURE);
  }

  num_values = atoi(argv[1]);
  if (num_values <= 0) {
    printf("Number of integers must be positive.\n");
    exit(EXIT_FAILURE);
  }

  values = (int *)malloc(num_values * sizeof(int));
  if (values == NULL) {
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      printf("Unable to open the input file.\n");
      free(values);
      exit(EXIT_FAILURE);
    }
  } else {
    file = stdin;
    printf("Enter %d integers for me to average:\n", num_values);
  }

  for (i = 0; i < num_values; i++) {
    if (fscanf(file, "%d", &values[i]) != 1) {
      printf("Failed to read integer.\n");
      free(values);
      if (file != stdin)
        fclose(file);
      exit(EXIT_FAILURE);
    }
  }

  if (file != stdin)
    fclose(file);

  for (i = 0; i < num_values; i++) {
    sum += values[i];
  }
  mean = sum / num_values;

  for (i = 0; i < num_values; i++) {
    sum_sq_diff += pow(values[i] - mean, 2);
  }
  stdev = sqrt(sum_sq_diff / (num_values - 1));

  free(values);

  printf("Mean: %f\n", mean);
  printf("Standard Deviation: %f\n", stdev);

  return 0;
}
