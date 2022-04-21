#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void exit(int status);
int atoi(const char *str);
void *malloc(size_t size);

int main(int argc, char *argv[]) {

  FILE *file;

  int i;
  int n = 0;
  int *a;

  float mean, stdev, temp1;
  float sum = 0;
  float temp2 = 0;

  if (argc == 3) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      printf("Unable to open the input file.\n");
      exit(-1);
    } else {
      n = atoi(argv[1]);
      a = (int *)malloc(n * sizeof(int));
      for (i = 0; i < n; i++) {
        fscanf_s(file, "%d", &a[i]);
      }
      free(a);
    }
  } else {
    if (argc == 2) {
      file = stdin;
      n = atoi(argv[1]);
      a = (int *)malloc(n * sizeof(int));
      printf("\n\nEnter %d integers for me to average:\n\n", n);
      for (i = 0; i < n; i++) {
        fscanf_s(file, "%d", &a[i]);
      }
      free(a);
    } else {
      printf("\n\nUsage: %s num_int_to_avg\n\nE.g.\n./avg 3\nEnter 3 integers "
             "for me to average:\n1 3 3\nmean: 2.333333\nstandard deviation: "
             "1.154701\n",
             argv[0]);
      exit(-1);
    }
  }
  for (i = 0; i < n; i++) {
    sum = sum + a[i];
  }
  mean = sum / n;
  for (i = 0; i < n; i++) {
    temp1 = pow(a[i] - mean, 2);
    temp2 = temp1 + temp2;
  }
  stdev = sqrt(temp2 / (n - 1));
  printf("Mean: %f\n", mean);
  printf("standard deviation: %f\n", stdev);
}
