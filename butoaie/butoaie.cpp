#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h> 
// constraints
#define MAXN 200000
using namespace std;
// input data
long long int N, K, Q, P, i, result;
long long int V[MAXN];

//-1 decrease, 0 found, 1 increase
int IsSufficient(int min, int offset){
    int result;

    

    return result;
}

//Calculate minimun of days needed for kill all bugs everywhere
long long int GetDays() {
    long long int maxIndex = N-1, minIndex = 0;
    //1 step - find most efficient bug killer
    long long int eff = Q > P ? Q : P;
    long long int neff = Q > P ? P : Q;

    //2 step - find min and max days
    long long int minDays = V[0] / eff + (V[0] % eff == 0 ? 0 : 1);
    long long int maxDays = V[0] / neff + (V[0] % neff == 0 ? 0 : 1);

    //3 step - try days
    long long int days = maxDays - minDays / 2;
    int todo = IsSufficient(minDays, days);
    
    while(todo != 0) {
        days += todo;
        todo = IsSufficient(minDays, days);
    }

    return days;
}

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d%d", &N, &K));
    assert(2 == scanf("%d%d", &P, &Q));
    for(i=0; i<N; i++)
        assert(1 == scanf("%d", &V[i]));

    result = GetDays();

    printf("%d\n", result); // print the result
    return 0;
}