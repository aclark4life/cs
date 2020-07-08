

void quicksort(int lo, int hi) {
  int position;
  int i;

  if (lo < hi) {
    position = partition(lo, hi);
    quicksort(lo, position - 1);
    quicksort(position + 1, hi);
  }
}
