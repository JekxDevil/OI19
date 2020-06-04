#include <stdio.h>
#include <assert.h>

// constraints
#define MAXN 1000000
#define SUFFICIENT 6

// input data
int N, i;
int G[MAXN];

long long GetGrades(){
    long long _result, j, _insufficientIndex, _sufficientIndex;

    j = 0;
    while(G[j] >= SUFFICIENT){
        j++;
    }

    _insufficientIndex = j;
    j = N-1;

    while(G[j] < SUFFICIENT){
        j--;
    }
    
    _sufficientIndex = j;
    _result = 1 + _sufficientIndex - _insufficientIndex;
    
    return _result <= 0 ? -1 : _result;
}

int main() {
    assert(1 == scanf("%d", &N));
    
    for(i=0; i<N; i++)
        assert(1 == scanf("%d", &G[i]));

    long long result = GetGrades();
    
    printf("%d\n", result); // print the result
    return 0;
}
