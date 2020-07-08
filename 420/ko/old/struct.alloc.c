
struct element {
  int value;
  int row;
  int col;
  struct element *next_row;
  struct element *next_col;
};

main() {
  struct element fred, bob, *henry, *new;
  new = (struct element *)malloc(sizeof(struct element));

  henry = (struct element *)malloc(sizeof(struct element));
  henry->value = 789;
  henry->row = 3;
  henry->col = 35;
  henry->next_row = &bob;
  henry->next_col = &fred;
  fred.value = 42;
  fred.row = 75;
  fred.col = 92;
  fred.next_row = &bob;
  fred.next_col = new;
  bob.value = 3412;
  bob.row = 4;
  bob.col = 32;
  bob.next_row = &fred;
  bob.next_col = henry;
}
