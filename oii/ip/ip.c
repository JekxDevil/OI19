#include <stdio.h>

union ip {
  unsigned char a[4];
  unsigned int num;
};

int main(void) {
  union ip ip1, ip2;
  scanf("%hhu.%hhu.%hhu.%hhu", &ip1.a[3], &ip1.a[2], &ip1.a[1], &ip1.a[0]);
  scanf("%hhu.%hhu.%hhu.%hhu", &ip2.a[3], &ip2.a[2], &ip2.a[1], &ip2.a[0]);
  printf("%lu\n", (unsigned long int)ip2.num - (unsigned long int)ip1.num + 1);
}
