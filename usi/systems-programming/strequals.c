#include <stdio.h>

int stringequal(const char *s1, const char *s2);

int main () {
  printf("%d", stringequal("lmao", "lmao"));
}

int stringequal(const char *s1, const char *s2) {
  while (*s1 != '\0') {
    if (*s1 != *s2) return 0;
    s1 += 1;
    s2 += 1;
  }

  return *s2 == '\0';
}
