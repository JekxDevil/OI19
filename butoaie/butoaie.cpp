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
int N, K, Q, P, i, result;
int V[MAXN];

int array_test[MAXN];
int* high_anti_insect;
int* weak_anti_insect;
int efficient_difference;
int bugs_killed_per_day;
int total_bugs_left;

//-1 decrease, 1 increase
int IsSufficient(int _day){
    int8_t result;
    int weak_kills = Q * _day;
    int left_kills = efficient_difference * _day;
    int surely_completed;

    int still_bugs_index;
    int i = 0;
      int tmp;

    do {
        array_test[i] = V[i] - weak_kills;
    } while (i < N && array_test[i++] > 0);

    still_bugs_index = i - 1;
    i = 0;

    do{
        tmp = array_test[i] - left_kills;

        if(tmp > 0) {
            result = INCREASE;
        }
    } while (still_bugs_index > i++);

    if(tmp < 0)
        result = DECREASE;

    return result;
}

//Calculate minimun of days needed for kill all bugs everywhere
int GetDays() {
    int days;
    int most_bugs_populated_room = 0;
    int max_possible_days, min_possible_days;
    bugs_killed_per_day = (K * P) + ((N - K) * Q);
    total_bugs_left = 0;

    //decreasing
    sort(V, V+N, greater<int>());
    
    if(V[0] == 0) {
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
            weak_anti_insect = &K;
        }

        efficient_difference = P - Q;
        int relative_min_days = total_bugs_left / bugs_killed_per_day;
        int min_anti_insect_days = most_bugs_populated_room / P;
        int max_anti_insect_days = most_bugs_populated_room / Q;

        if(total_bugs_left % bugs_killed_per_day > 0)
            relative_min_days++;

        if(most_bugs_populated_room % P > 0)
            min_anti_insect_days++;

        if(most_bugs_populated_room % Q > 0)
            max_anti_insect_days++;

        min_possible_days = max(relative_min_days, min_anti_insect_days);   //max secondo prof
        max_possible_days = max_anti_insect_days;

        //binary search
        short int flag;

        for(int i = 0; min_anti_insect_days != max_anti_insect_days; i++){
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d%d", &N, &K));
    assert(2 == scanf("%d%d", &P, &Q));
    for(i=0; i<N; i++)
        assert(1 == scanf("%d", &V[i]));

    result = GetDays();

    printf("%d\n", result); // print the result
    return 0;
}