#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
void pv(vector<int> v, string s);

//#define pv //

long long int D, N, day;
vector<int> business;
vector<int> choose;
vector<int> maybe;
long long int maxnow, maxsum;
long long int maxprev = -1, maxprevsum = -1, maxprevindex = 1;

int main(){

    ////////////////////// INPUT/OUTPUT
    cin >> D >> N;
    int tmp;
    for(int i = 0; i < N; i++){
        cin >> tmp;
        business.push_back(tmp);
    }

    if(D > N){
        cout << "impossible" << endl;
        return 0;
    }

    //pv(business, "business");
    ////////////////////////

    /////////////////////// FIRST VECTOR
    choose = {business.begin(), business.begin() + D};
    //pv(choose, "choose");
    maxprev = *max_element(choose.begin(), choose.end()); //max
    maxprevsum = accumulate(choose.begin(), choose.end(), 0);

    //cout << maxprev << " " << maxprevn << " " << endl << endl;    // DEBUG
    /////////////////////////

    ///////////////////////// COMPARISONS SLIDING WINDOWS
    for(int i = 1; i < N-D+1; i++){

        // BUILD NEXT WINDOWS
        maybe = {business.begin() + i, business.begin() + D + i};
        //pv(maybe, "maybe");
        maxnow = *max_element(maybe.begin(), maybe.end()); //max
        maxsum = accumulate(maybe.begin(), maybe.end(), 0); // sum
        //cout << "LOOP -- maxchoose: " << maxchoose << " | maxn: " << maxn << " | DAY: " << i+1 << endl << endl;   //DEBUG


        // COMPARE MOST BUSY DAY IN WINDOW (WINS THE LEAST)
        if(maxprev > maxnow) {
            maxprev = maxnow;
            maxprevsum = maxsum;
            maxprevindex = i + 1;

            //cout << "MAXPREV > MAXCHOOSE -- maxprev: " << maxprev << " | maxprevn: " << maxprevn << " | DAY: " << maxprevindex << endl << endl;   //DEBUG

        // COMPARE MOST BUSY DAYS IN WINDOWS IF MAX BUSINESS IS THE SAME
        } else if(maxprev == maxnow) {
            if(maxprevsum > maxsum){
                maxprev = maxnow;    //redundant
                maxprevsum = maxsum;
                maxprevindex = i + 1;
            }

            // DAYS: COMPARE BEFORENESS IF MAX BUSINESS AND NUM MAX BUSINESS ARE EQUAL (SAME VECTORS)
            //cout << "IMPLICIT -- maxprev: " << maxprev << " | maxprevsum: " << maxprevsum << " | DAY: " << maxprevindex << endl << endl;  //DEBUG
        }
    }

    cout << maxprevindex << endl;
    return 0;
}


/*
2 10
4 3 7 1 12 2 3 5 8 4

6

////
4 3
10 2 1

impossible
////
3 15
9 1 3 2 5 10 8 2 3 3 1 3 4 0 0

2

///
3 3
1 2 3

1
*/


void pv(vector<int> v, string s){
    cout << s << ": ";
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}
