#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

//remember that K killing P and N-K killing Q is equal N killing Q and K killing P-Q

// constraints
#define MAXN 200000
using namespace std;

// input data
long long int N, K, Q, P, i, result;
long long int V[MAXN];

long long int total_bugs = 0;
long long int total_daily_kill;
long long int kill_low;
long long int kill_left;
long long int array_test[MAXN];

//State if days clear all rooms or not
bool RightDays(long long int _days){
    long long int left_position, first_step, antisects_left, bugs_left, tmp, i;
    bugs_left = 0;
    left_position = N;  //start since, then decrease
    first_step = kill_low * _days;

    //subtract from all rooms q bugs and get index since when there are no more bugs (needs decreasing sorting)
    for(i = 0; i < N; i++){
        tmp = V[i] - first_step;
        array_test[i] = std::max(tmp, (long long)0);
        bugs_left += array_test[i];
        
        if(!array_test[i]){
            left_position = i;
            break;
        }
    }

    //number of antisects remaining for usage
    antisects_left = K * _days;

    //quick end, there are globally enough antisects to kill all remaining bugs
    if(antisects_left * kill_left < bugs_left)
        return false;

    //see if antisects remaining are enough to clear all rooms
    for(i = 0; i < left_position; i++){
        tmp = array_test[i] / kill_left;

        if(array_test[i] % kill_left)
            tmp++;
        
        if(tmp <= antisects_left)
            antisects_left -= tmp;
        else
            return false;

    }

    return true;
}

//get the minimum number of days needed for cleaning all rooms
long long int GetDays(){
    long long int tmp, relative_min_range, min_range, max_range, days;

    //array sort decreasing
    std::sort(V, V+N, greater<int>());

    //P always greater
    if(P < Q){
        tmp = P;
        K = N - K;
        P = Q;
        Q = tmp;
    }

    //if rooms are already empty
    if(V[0] == 0)
        return 0;

    //only one antisect case
    if(K == N || K == 0 || P == Q)
    {   
        if(K == 0)
            P = Q;

        days = V[0] / P;
        
        if(V[0] % P)
            days++;
            
        return days;
    }
    else
    {
        total_daily_kill = (long long)K * P + (long long)(N - K) * Q;
        kill_low = Q;
        kill_left = P - Q;

        //max and min days required
        relative_min_range = Q != 0 ? total_bugs / total_daily_kill : 0;
        min_range = V[0] / P;

        if(V[0] % P)
            min_range++;

        min_range = std::max(min_range, relative_min_range);
        max_range = V[0] / Q + 1;

        //quick end
        if(RightDays(min_range))
            return min_range;

        //binary search
        while(min_range + 1 < max_range)
        {   
            days = (min_range + max_range) / 2;

            if(RightDays(days))
                max_range = days;
            else 
                min_range = days;
        }
        
        return max_range;
    }
}

int main() {
//  uncomment the following lines if you want to read/write from files
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    assert(2 == scanf("%lld%lld", &N, &K));
    assert(2 == scanf("%lld%lld", &P, &Q));

    for(i=0; i<N; i++){
        assert(1 == scanf("%lld", &V[i]));
        total_bugs += V[i];
    }

    result = GetDays();

    printf("%lld\n", result); // print the result
    return 0;
}