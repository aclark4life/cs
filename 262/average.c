#include <math.h>
#include <stdio.h>

void exit(int status);
int atoi(const char *str);
void *malloc(size_t size);

int main(int argc, char *argv[]) {
  FILE *infile;
  int i, n = 0, *a;
  float sum, mean, stdev, temp1, temp2;
  if (argc == 3) {
    infile = fopen(argv[2], "r");
    if (infile == NULL) {
      printf("Unable to open the input file.\n");
      exit(-1);
    } else {
      n = atoi(argv[1]);
      a = (int *)malloc(n * sizeof(int));
      for (i = 0; i < n; i++) {
        fscanf(infile, "%d", &a[i]);
      }
    }
  } else {
    if (argc == 2) {
      infile = stdin;
      n = atoi(argv[1]);
      a = (int *)malloc(n * sizeof(int));
      printf("enter %d integers:\n", n);
      for (i = 0; i < n; i++) {
        fscanf(infile, "%d", &a[i]);
      }
    } else {
      printf("usage: %s n\n", argv[0]);

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
  printf("mean: %f\n", mean);
  printf("standard deviation: %f\n", stdev);
}
