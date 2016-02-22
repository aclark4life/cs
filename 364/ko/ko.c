#include <stdio.h>
#include <math.h>

void print_array(int **array, int row, int col);
void print_count_array(int col);
struct node {
  int winner;
  int loser;
  int index;
  int lindex;
  int winner_index;
  int loser_index;
};

main(int argc, char *argv[]) {
  int i, j, ii = 0;
  int k, l = 1;
  int row, row_index = 0;
  int **temp_array;
  int *count_array;
  struct node *node;
  int power, pass, pass_index;
  int height, compare, winner;
  int temp, temp_index, output, index;
  int loser_index;
  int outer_loop_length = 8;
  int new;
  FILE *outfile;

  if (argc != 3) {
    printf("USAGE IS: n m\n", argv[0]);
    exit(-1);
  } else {
    int max_row = atoi(argv[1]);
    int max_col = atoi(argv[2]);

    temp_array = (int **)malloc(max_row + 1 * sizeof(int));
    for (i = 0; i < max_row + 1; i++)
      temp_array[i] = (int *)malloc((max_col * 2) * sizeof(int));
    for (i = 0; i < max_row + 1; i++) {
      for (j = 0; j < max_col * 2 - 1; j++) {
        temp_array[i][j] = 0;
        for (j = max_col; j < max_col * 2; j++) {
          temp_array[i][j] = k;
          k++;
        }
      }
      for (j = 0; j < max_col * 2; j++) {
        temp_array[max_row + 1][j] = -1;
      }
    }
    print_array(temp_array, max_row, max_col);
    printf("\n");
    node = (struct node *)malloc(max_col * sizeof(struct node));
    for (i = max_col, j = max_col / 2; i < max_col * 2; i += 2, j++) {
      if (temp_array[row][i] < temp_array[row][i + 1]) {
        node[j].winner = temp_array[row][i];
        node[j].loser = temp_array[row][i + 1];
        node[j].winner_index = i;
        node[j].loser_index = i + 1;
        node[j].lindex = i / 2;
        temp_array[row][node[j].lindex] = node[j].loser;
      } else {
        node[j].winner = temp_array[row][i + 1];
        node[j].loser = temp_array[row][i];
        node[j].winner_index = i + 1;
        node[j].loser_index = i;
        node[j].lindex = i / 2;
        temp_array[row][node[j].lindex] = node[j].loser;
      }
    }

    for (i = (max_col - 1), j = ((max_col / 2) - 1); i > 0; i -= 2, j--) {
      if (node[i - 1].winner < node[i].winner) {
        node[j].winner = node[i - 1].winner;
        node[j].loser = node[i].winner;
        node[j].winner_index = node[i - 1].winner_index;
        node[j].loser_index = node[i].winner_index;
        node[j].lindex = i / 2;
        temp_array[row][node[j].lindex] = node[j].loser;
      } else {
        node[j].winner = node[i].winner;
        node[j].loser = node[i - 1].winner;
        node[j].winner_index = node[i].winner_index;
        node[j].loser_index = node[i - 1].winner_index;
        node[j].lindex = i / 2;
        temp_array[row][node[j].lindex] = node[j].loser;
      }
    }

    /*    print_array(temp_array, max_row, max_col);
       printf("\n");
        for(i=1;i<max_col;i++){
          printf("node[%d].winner = %d   ",i, node[i].winner);
          printf("node[%d].loser = %d\n",i, node[i].loser);
          } printf("\n");
        for(i=1;i<max_col;i++){
          printf("node[%d].winner_index = %d   ",i, node[i].winner_index);
          printf("node[%d].loser_index = %d\n", i ,node[i].loser_index);
        } printf("\n");
        printf("output> %d\n",node[1].winner);
        print_array(temp_array, max_row, max_col);

       */

    row_index++;
    index = node[1].winner_index;
    pass_index = node[1].winner_index;

    for (ii = 0; ii < outer_loop_length; ii++) {
      temp_array[row][pass_index] = temp_array[row_index][pass_index];
      pass = temp_array[row_index][pass_index];
      height = 3;
      for (i = 1; i < height; i++) {
        power = pow(2, i);

        /*	printf("pass> %d\n", pass);
                printf("cue> %d\n", temp_array[row][pass_index/power]);

        */
        if (pass < temp_array[row][pass_index / power]) {

          /*	  printf("%d < %d\n",pass, temp_array[row][pass_index/power]);

                   */
        } else {
          /* printf("%d < %d\n",temp_array[row][pass_index/power],pass);
           printf("replace %d with %d ",temp_array[row][pass_index/power],pass);
            */
          temp = pass;
          pass = temp_array[row][pass_index / power];
          pass_index = node[pass_index / power].loser_index;

          /*  printf("and pass -> %d\n", pass);
            printf("pass_index> %d\n", pass_index);
             */
          temp_array[row][pass_index / power] = temp;
          loser_index = node[pass_index / power].winner_index;

          /*	  printf("loser_index> %d\n", loser_index);
                   */
          node[pass_index / power].loser = temp_array[row][pass_index / power];
          node[pass_index / power].winner = pass;

          node[pass_index / power].loser_index = loser_index;
          node[pass_index / power].winner_index = pass_index;
        }
      }
      node[1].winner = pass;
      node[1].winner_index = pass_index;
      output = pass;
      printf("output> %d\n", output);
      /*
      print_array ( temp_array, max_row, max_col);
      for(i=1;i<max_col;i++){
        printf("node[%d].winner = %d   ",i, node[i].winner);
        printf("node[%d].loser = %d\n",i, node[i].loser);
      } printf("\n");
      for(i=1;i<max_col;i++){
        printf("node[%d].winner_index = %d   ",i, node[i].winner_index);
        printf("node[%d].loser_index = %d\n", i ,node[i].loser_index);
      } printf("\n");

      */
    }
  }
}

void print_array(int **array, int row, int col) {
  int i;
  int j;
  for (i = 0; i < row; i++) {
    for (j = 1; j < col * 2; j++) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
  for (i = row + 1; i < row + 2; i++) {
    for (j = 1; j < col * 2; j++) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}

void print_count_array(int col) {
  int i;
  int l = 1;
  int *array;
  array = (int *)malloc((col * 2 - 1) * sizeof(int));
  for (i = 0; i < (col * 2 - 1); i++) {
    array[i] = l;
    l++;
    printf("%d ", array[i]);
  }
  printf("\n");
  for (i = 0; i < (25); i++) {
    printf("-");
  }
  printf("\n");
}
