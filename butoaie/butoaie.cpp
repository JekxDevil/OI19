#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h> 
// constraints
#define MAXN 200000
#define DECREASE -1
#define INCREASE 1
using namespace std;
// input data
long long int N, K, Q, P, i, result;
long long int V[MAXN];

long long int array_test[MAXN];
long long int* high_anti_insect;
long long int* low_anti_insect;
long long int efficient_difference;
long long int bugs_killed_per_day;

//-1 decrease, 0 found, 1 increase
int IsSufficient(int day){
    short int result;

    

    return result;
}

//Calculate minimun of days needed for kill all bugs everywhere
long long int GetDays() {
    long long days;
    long long most_bugs_populated_room = 0;
    long long total_bugs_left = 0;
    long long max_possible_days, min_possible_days;
    bugs_killed_per_day = (K * P) + ((N - K) * Q);

    //decreasing
    sort(V, V+N, greater<long long int>());
    
    if(V[0] == 0){
        days = 0;
    } else {
        most_bugs_populated_room = V[0];
        
        //calculating most populated room and total bugs
        for(int i = 0; i < N; i++) {
            total_bugs_left += V[i];
        }

        //p always greater
        if(P < Q) {
            int tmp = Q;
            Q = P;
            P = tmp;
            *high_anti_insect = N - K;
            low_anti_insect = &K;
        }

        efficient_difference = P - Q;
        long long relative_min_days = total_bugs_left / bugs_killed_per_day;
        long long min_anti_insect_days = most_bugs_populated_room / P;
        long long max_anti_insect_days = most_bugs_populated_room / Q;

        if(total_bugs_left % bugs_killed_per_day > 0)
            relative_min_days++;

        if(most_bugs_populated_room % P > 0)
            min_anti_insect_days++;

        if(most_bugs_populated_room % Q > 0)
            max_anti_insect_days++;

        min_possible_days = min(relative_min_days, min_anti_insect_days);   //max secondo prof
        max_possible_days = max_anti_insect_days;

        //binary search
        short int flag = DECREASE;

        for(int i = 0; flag != 0; i++){
            days = (max_anti_insect_days - min_anti_insect_days) / 2;

            //continuare
            switch (flag = IsSufficient(days))
            {
            case DECREASE:
                max_anti_insect_days = days;
                break;
            
            case INCREASE:
                min_anti_insect_days = days;
                break;
            }
        }
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