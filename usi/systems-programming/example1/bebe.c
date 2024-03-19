#include <stdio.h>

int main() {
  // read from input and tell how many characters there are
  int mychar = getchar();
  int sum = 0;
  while(mychar != EOF) {
    sum++;
    mychar = getchar();
  }
  printf("characters = %d\n", sum);
  return 0;
 }

