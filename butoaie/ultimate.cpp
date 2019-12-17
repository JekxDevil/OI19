#include <stdio.h>
#include <assert.h>
#include <iostream>

// constraints
#define MAXN 200000
using namespace std;

// input data
int N, K, Q, P, i, result;
int V[MAXN];

int max_bugs = 0;
int total_bugs = 0;
int total_daily_kill;
int kill_low;
int kill_left;
int array_test[MAXN];

bool IsSufficient(int _days){
    int left_position, tmp;

    for(int i = 0; i < N; i++){
        tmp = V[i] - (kill_low * _days);
        array_test[i] = std::max(tmp, 0);
        
        if(!array_test[i])
            left_position = i - 1;
    }
    
    if(left_position >= K)
        return false;

    for(int i = 0; i < left_position; i++){
        tmp = array_test[i] - kill_left * _days;
        array_test[i] = std::max(tmp, 0);

        if(array_test[i])
            return false;
    }

    return true;
}

int GetDays(){
    int relative_min_range, min_range, max_range, days;

    //P always greater
    if(P < Q){
        int tmp = P;
        K = N - K;
        P = Q;
        Q = tmp;
    }

    total_daily_kill = (K * P) + ((N - K) * Q);
    kill_low = Q;
    kill_left = P - Q;

    //max and min days required
    relative_min_range = total_bugs / total_daily_kill + 1;
    min_range = std::max(max_bugs / P + 1, relative_min_range);  //better more large than more restrictive 
    max_range = max_bugs / Q + 1;    //same as before but for min

    //binary search
    while(max_range != min_range + 1){
        days = (min_range + max_range) / 2;
        
        if(IsSufficient(days)){
            max_range = days;
        } else {
            min_range = days;
        } 
    }

    days = max_range;
    return days;
}

int main() {
//  uncomment the following lines if you want to read/write from files
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d%d", &N, &K));
    assert(2 == scanf("%d%d", &P, &Q));

    for(i=0; i<N; i++){
        assert(1 == scanf("%d", &V[i]));
        total_bugs += V[i];

        if(V[i] > max_bugs)
            max_bugs = V[i];
    }

    result = GetDays();

    printf("%d\n", result); // print the result
    return 0;
}