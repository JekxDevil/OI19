#include <bits/c++.h>
using namespace std;
int K, M, N;

int main (void) {
    cin >> K >> M >> N;
    long long int power = pow(K, M+N);
    // find numerator for input3
    // generalize m, n scope in numerator (1, 1) for input 3
    // calculate new numerator generalized
    // divide by denom and find reciprocal by doing min(m,n) - [first probability found]

    return 0;
}

/*
6 3 2

0.92091
1.07909
----------
4 4 2

0.86914
1.13086
----------
2 1 1

0.75000
0.25000
*/