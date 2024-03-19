#include <iostream>
#include <map>

int main(void) {
  std::map<int, unsigned> C;

  int tmp;
  while (std::cin >> tmp) {
    C[tmp] += 1;
  }

  for (auto it : C) {
    std::cout << it.first << " " << it.second << std::endl;
  }
  return 0;
}

