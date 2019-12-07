#include <assert.h>
#include <stdio.h>

#define MAXN 1000000

// input data
int N;
int P[MAXN];

long long GetTotalCost(){
  long long _result = P[0], _most_valuable = P[0];
  
  for(int i = 1; i < N; i++)
    if(_most_valuable < P[i]){
      _most_valuable = P[i];
      _result += _most_valuable;
    }

  return _result;
}

int main() {
  assert(1 == scanf("%d", &N));
  for (int i = 0; i < N; i++) assert(1 == scanf("%d", &P[i]));

  // insert your code here
  long long res = GetTotalCost();

  printf("%lld\n", res);  // print the result
  return 0;
}
