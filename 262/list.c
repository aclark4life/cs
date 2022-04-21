#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/

struct element {
  int value;
  int row;
  int col;
  struct element *next_row;
  struct element *next_col;
};

struct element *create_anchor_node(int row, int col) {
  struct element *a = (struct element *)malloc(sizeof(struct element));
  a->row = row;
  a->col = col;
  return (a);
};

struct element *create_head_node(struct element *anchor) {
  struct element *a = (struct element *)malloc(sizeof(struct element));
  anchor->next_row = a;
  a->next_row = a;
  a->next_col = a;
  a->row = -1;
  a->col = -1;
  return (a);
};

/*****************************************************************************/
struct element *do_col(struct element *new_node, struct element *head) {
  struct element *current;
  struct element *prev;

  current = head;
  prev = head;

  while (current->next_col != head) {

    current = current->next_col;

    if (new_node->col < current->col) {
      new_node->next_col = current;
      prev->next_col = new_node;
      return (head);
    }
    prev = current;
  }
  current->next_col = new_node;
  new_node->next_col = head;
  return (head);
}

/*****************************************************************************/
struct element *add_matrix(struct element *head1, struct element *head2) {

  struct element *temp1;
  struct element *temp2;

  return (temp1);
}

/*****************************************************************************/

struct element *insert_node(struct element *new_node, struct element *head) {

  /* this is a BIG mess, but it works... */

  struct element *current;
  struct element *prev;

  if (head->next_row->row == -1) {

    head->next_row = new_node; /*FIRST TIME!!!!!!!!!!!!!!*/
    new_node->next_row = head;

    head->next_col = new_node;
    new_node->next_col = head;
    return (head);

  }

  else { /*NOT THE FIRST TIME!!!!!!!!!!!!!!!!!!!!!!!!*/
    current = head;
    prev = head;

    while (current->next_row != head) {

      current = current->next_row;
      if (new_node->row < current->row) {

        /*insert NEW_NODE->ROW*/
        new_node->next_row = current;
        prev->next_row = new_node;

        /*do_col(head, new_node);*/

        /******************************************************/
        current = head;
        prev = head;

        while (current->next_col != head) {

          current = current->next_col;

          if (new_node->col < current->col) {

            /*insert NEW_NODE->COL*/
            new_node->next_col = current;
            prev->next_col = new_node;
            return (head);
          }

          /**************************************************************/
          if (new_node->col == current->col) {

            /*insert NEW_NODE->COL*/
            new_node->next_col = current;
            prev->next_col = new_node;
            return (head);
          }
          /**************************************************************/

          prev = current;
        }

        /*insert NEW_NODE->COL at end of list*/
        current->next_col = new_node;
        new_node->next_col = head;
        return (head);
      }

      /**************************************************************/
      if ((new_node->row == current->row) && (new_node->col == current->col)) {

        current->value = new_node->value;
        return (head);
      }
      /**************************************************************/

      if (new_node->row == current->row) {

        /*insert NEW_NODE->ROW*/
        new_node->next_row = current;
        prev->next_row = new_node;

        /*do_col(head, new_node);*/

        /******************************************************/
        current = head;
        prev = head;

        while (current->next_col != head) {

          current = current->next_col;

          if (new_node->col < current->col) {

            /*insert NEW_NODE->COL*/
            new_node->next_col = current;
            prev->next_col = new_node;
            return (head);
          }
          prev = current;

          /**************************************************************/
          if (new_node->col == current->col) {

            /*insert NEW_NODE->COL*/
            new_node->next_col = current;
            prev->next_col = new_node;
            return (head);
          }
          /**************************************************************/
        }

        /*insert NEW_NODE->COL at end of list*/
        current->next_col = new_node;
        new_node->next_col = head;
        return (head);
      }

      prev = current;

    } /*END while(current->next_row != head)*/

    /*insert NEW_NODE->ROW at the end of list*/
    current->next_row = new_node;
    new_node->next_row = head;

    /*do_col(head, new_node);*/

    /******************************************************/
    current = head;
    prev = head;

    while (current->next_col != head) {

      current = current->next_col;

      if (new_node->col < current->col) {

        /*insert NEW_NODE->COL*/
        new_node->next_col = current;
        prev->next_col = new_node;
        return (head);
      }

      /**************************************************************/
      if (new_node->col == current->col) {

        /*insert NEW_NODE->COL*/
        new_node->next_col = current;
        prev->next_col = new_node;
        return (head);
      }
      /**************************************************************/

      prev = current;
    }

    /*insert NEW_NODE->COL at end of list*/
    current->next_col = new_node;
    new_node->next_col = head;
    return (head);

    /******************************************************/

    return (head);

  } /*END else*/
} /*END insert_node*/

/*****************************************************************************/

void print_matrix(struct element *head) {

  struct element *e;
  printf("PRINT_BY_ROW>\n\n");
  for (e = head->next_row; e->row != -1; e = e->next_row) {

    printf("ROW> %d           ", e->row);
    printf("COL> %d           ", e->col);
    printf("VALUE> %d\n", e->value);
  }

  printf("\n");
  printf("PRINT_BY_COLUMN>\n\n");
  for (e = head->next_col; e->col != -1; e = e->next_col) {

    printf("COL> %d           ", e->col);
    printf("ROW> %d           ", e->row);
    printf("VALUE> %d\n", e->value);
  }
  printf("\n>");
}

/*****************************************************************************/

void print_menu() {

  system("clear"); /*clear the screen*/
  printf("\n JOHNNY LINK A LIST (UNDER CONSTRUCTION)\n\n");
  printf("****************************************************************\n");
  printf(" 1) CREATE MATRIX ONE\n");
  printf(" 2) CREATE MATRIX TWO\n");
  printf(" 3) PRINT MATRIX\n");
  printf(" 4) add matrix\n");
  printf(" 5) subtract matrix\n");
  printf(" 6) multiply matrices\n");
  printf(" 7) transpose a matrix\n");
  printf(" 8) NOTE TO KBG\n");
  printf("****************************************************************\n");
  printf("(q = QUIT)\n");
  printf("\nJOHNNY_SAYS> ");
}

/*****************************************************************************/

void menu() {
  int gaurd1 = 0;
  int gaurd2 = 0;
  char print = 0;
  char add = 0;
  char foo = 0;
  int max_row1;
  int max_col1;
  int i;
  int col1 = 0;
  int row1 = 0;
  int value;
  int number_of_nodes;

  struct element *head1;
  struct element *anchor1;
  struct element *node1;

  struct element *head2;
  struct element *anchor2;
  struct element *node2;

  anchor1 = (struct element *)create_anchor_node(max_row1, max_col1);
  anchor2 = (struct element *)create_anchor_node(max_row1, max_col1);
  head1 = create_head_node(anchor1);
  head2 = create_head_node(anchor2);

  while (foo != 'q') {

    print_menu();
    scanf("%c", &foo);
    rewind(stdin);
    switch (foo) {
    /*********************************************************************/
    case '1': /*MATRIX 1*/

    {
      system("clear");
      printf("(0 < MAX_ROW <= 20)\n");
      printf("(0 < MAX_COL <= 20)\n");
      printf("(0 < NUMBER_OF_NODES <= 20)\n\n");

      gaurd1 = 1;

      printf("MAX_ROW>");
      scanf("%d", &max_row1);

      if ((max_row1 > 0) && (max_row1 <= 20)) {
        max_col1 = max_col1;
      } else {
        exit(-1);
      }

      printf("MAX_COL>");
      scanf("%d", &max_col1);

      if ((max_col1 > 0) && (max_col1 <= 20)) {
        max_col1 = max_col1;
      } else {
        exit(-1);
      }

      anchor1 = (struct element *)create_anchor_node(max_row1, max_col1);
      head1 = create_head_node(anchor1);

      printf("NUMBER_OF_NODES> ");
      scanf("%d", &number_of_nodes);

      if ((number_of_nodes > 0) && (number_of_nodes <= 20)) {
        number_of_nodes = number_of_nodes;
      } else {
        exit(-1);
      }

      system("clear");

      /*********************************************************************/

      for (i = 1; i <= number_of_nodes; i++) { /*MATRIX 1*/

        printf("ROW>");
        scanf("%d", &row1);

        if ((row1 > 0) && (row1 <= max_row1)) {
          row1 = row1;
        } else {
          exit(-1);
        }

        printf("COL>");
        scanf("%d", &col1);

        if ((col1 > 0) && (col1 <= max_col1)) {
          col1 = col1;
        } else {
          exit(-1);
        }

        printf("VALUE>");

        scanf("%d", &value);
        system("clear");

        /*******************************************************************/

        node1 = (struct element *)malloc(sizeof(struct element));
        node1->row = row1;
        node1->col = col1; /*MATRIX 1*/
        node1->value = value;

        head1 = insert_node(node1, head1);

      } /*for*/

      break;
    }

    /***********************************************************************/
    case '2': {

      system("clear");

      gaurd2 = 1;

      printf("(0 < MAX_ROW <= 20)\n");
      printf("(0 < MAX_COL <= 20)\n");
      printf("(0 < NUMBER_OF_NODES <= 20)\n\n");

      printf("MAX_ROW>"); /*MATRIX 2*/
      scanf("%d", &max_row1);
      rewind(stdin);
      if ((max_row1 > 0) && (max_row1 <= 20)) {
        max_row1 = max_row1;
      } else {
      }

      printf("MAX_COL>");
      scanf("%d", &max_col1);

      if ((max_col1 > 0) && (max_col1 <= 20)) {
        max_col1 = max_col1;
      } else {
      }

      anchor2 = (struct element *)create_anchor_node(max_row1, max_col1);
      head2 = create_head_node(anchor2);

      printf("NUMBER_OF_NODES> ");
      scanf("%d", &number_of_nodes);

      if ((number_of_nodes > 0) && (number_of_nodes <= 20)) {

        number_of_nodes = number_of_nodes;
      } else {
        exit(-1);
      };
      system("clear");

      /*********************************************************************/

      for (i = 1; i <= number_of_nodes; i++) { /*MATRIX 2*/

        printf("ROW>");
        scanf("%d", &row1);

        if ((row1 > 0) && (row1 <= max_row1)) {
          row1 = row1;
        } else {
          exit(-1);
        }

        printf("COL>");
        scanf("%d", &col1);

        if ((col1 > 0) && (col1 <= max_col1)) {
          col1 = col1;
        } else {
          exit(-1);
        }

        printf("VALUE>");

        scanf("%d", &value);
        system("clear");

        /*******************************************************************/

        node2 = (struct element *)malloc(sizeof(struct element));
        node2->row = row1;
        node2->col = col1;
        node2->value = value;

        head2 = insert_node(node2, head2); /*MATRIX 2*/
      }

      break;
    }
      /***********************************************************************/

    case '3': {

      system("clear");
      while (print != 'q') {
        system("clear");
        printf("\n JOHNNY PRINT MATRIX\n\n");
        printf("********************************************************\n");
        printf(" 1) PRINT MATRIX ONE\n");
        printf(" 2) PRINT MATRIX TWO\n");
        printf("********************************************************\n");
        printf("(q = QUIT)\n");
        printf("\nJOHNNY_SAYS> ");
        scanf("%c", &print);
        rewind(stdin);
        switch (print) {
        case '1': {
          if (gaurd1 == 1) {

            system("clear");
            print_matrix(head1);
            getchar();
            break;
          }
        }
        case '2': {

          if (gaurd2 == 1) {

            system("clear");
            print_matrix(head2);
            getchar();
          }
          break;
        }
        default:
          break;

        } /*switch*/
        rewind(stdin);
      }
      print = 0;
      break;
    }

    case '4': {
      system("clear");

      printf(" JOHNNY ADD MATRIX (UNDER CONSTRUCTION)\n");
      printf("**************************************************\n");
      printf(" 1) MATRIX ONE + MATRIX TWO = MATRIX ONE\n");
      printf(" 2) MATRIX TWO + MATRIX ONE = MATRIX TWO\n");
      printf("**************************************************\n");
      printf("\nJOHNNY_SAYS> ");

      getchar();

      /*
         scanf("%c", &add);

         switch(add)
         {
         case '1':{
         add_matrix(head1,head2);

              break;
              }
              case '2':{

              break;
              }


              }

              }*/

      break;
    }
    case '5': {
      system("clear");
      printf(" JOHNNY SUB MATRIX (UNDER CONSTRUCTION)\n\n");
      printf("**********************************************************\n\n");
      printf("**********************************************************\n\n");
      printf("\nJOHNNY_SAYS> ");
      getchar();
      break;
    }
    case '6': {
      system("clear");
      printf(" JOHNNY MULTIPLY (UNDER CONSTRUCTION)\n\n");
      printf("**********************************************************\n\n");
      printf("**********************************************************\n\n");
      printf("\nJOHNNY_SAYS> ");
      getchar();

      break;
    }
    case '7': {
      system("clear");
      printf(" JOHNNY TRANSPOSE (UNDER CONSTRUCTION)\n\n");
      printf("**********************************************************\n\n");
      printf("**********************************************************\n\n");
      printf("\nJOHNNY_SAYS> ");
      getchar();
      break;
    }

    case '8': {
      system("clear");
      printf("kbg- spent many hours working on insert.\n");

      printf("it turned out to be real messy and complicated.\n");
      printf("i don't think it was the best way to do it but,\n");
      printf("i think it works correctly for every case.\n");
      printf("the function do_col is incomplete because i\n");
      printf("couldn't figure out how to pass to it. what i need is\n");
      printf("to put things in functions to reduce the code.\n");
      printf("also, only CAPITALIZED options work. i haven't\n");
      printf("figured out how to implement the rest of the options\n");
      printf("with the code i've written.\n");
      printf("HAPPY HOLIDAYS...\n");

      getchar();
      break;
    }

    case 'q':
      break;
    default:
      break;

    } /*END switch*/
    rewind(stdin);

  } /*END while (foo != 'q')*/
}

/*********************************************************************/

int main(int argc, char *argv[]) {
  if (argc != 1) {
    printf("USAGE: %s\n\n", argv[0]);
    exit(-1);
  }

  else {

    menu();

  } /*else*/
} /*end main*/
