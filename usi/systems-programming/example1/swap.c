#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
  int i, j;
  printf("input 2 integers: ");
  scanf("%d %d", &i, &j);
  printf("i = %d, j = %d\n", i, j);
  swap(&i, &i);
  printf("i = %d, j = %d\n", i, j);
  return 0;
}

void swap(int *a, int *b) {
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
 }

