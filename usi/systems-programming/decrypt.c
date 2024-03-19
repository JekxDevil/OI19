#include <stdio.h>
#include <limits.h>

int encrypt(int num);
int decrypt(int num);

int main() {
  int c;
  while ((c = getchar()) != EOF) {
      c = decrypt(encrypt(c));
      putchar(c);
  }
  return 0;
}

int encrypt(int num) {
  num += 3;
  if (num > UCHAR_MAX) num = num - UCHAR_MAX;
  return num;
}

int decrypt(int num) {
  num -= 3;
  if (num < 0) num = num + UCHAR_MAX;
  return num;
}
