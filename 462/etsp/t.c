

#include <stdio.h>
void well_heluuuu_there() {
  char *buf = (char *)malloc(sizeof(char));
  // int *buf=(int *)malloc(sizeof(int));
  FILE infile;

  // printf("%d\n",a);

  infile = fopen(stdin, "r");
  while (fgets(buf, 1, infile)) {
  }
}

void main(int argc, char *argv[]) {
  // char *helo;
  // int helo;
  // helo = malloc (sizeof (char *));
  // helo = argv[0];
  // helo = atoi(argv[1]);
  // well_heluuuu_there(helo);

  if (argc != 1) {
    printf("Sorry, i don't take command line arguments.\n");
    exit(-1);
  } else {
    well_heluuuu_there();
  }
  // printf("%d\n",helo);
}
