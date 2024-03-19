#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

int D, N;
//vector<int> days_needed;
vector<int> sched;
// find D days with min sum in sched

vector<int> choose;
vector<int> maybe;

int main(){
    cin >> D >> N;
    int tmp;
    for(int i = 0; i < N; i++){
        cin >> tmp;
        sched.push_back(tmp);
    }
    if(D > N){
        cout << "impossible" << endl;
        return 0;
    }
    if(D==N) {
        cout << 0 << endl;
        return 0;
    }
    int best_max = 1000000;
    vector<int> best_group_indexes;
    for(int i=0;i<N-D+1;i++){
        int temp_max = 0;
        for(int j=i;j<i+D;j++){
            if(sched[j]>temp_max) temp_max=sched[j];
        }
        if(temp_max<best_max){
            best_group_indexes.clear();
            best_group_indexes.push_back(i);
            best_max = temp_max;
        }else if(temp_max == best_max){
            best_group_indexes.push_back(i);
        }
    }

    if(best_group_indexes.size()==1){
        cout << best_group_indexes[0] << endl;
        return 0;
    }

    vector<pair<vector<int>,int>> best_groups;
    for(int index : best_group_indexes){
        vector<int> group = {sched.begin()+index, sched.begin()+index+D};
        sort(group.begin(), group.end(), greater<int>());
        pair<vector<int>, int> pair;
        pair.first = group;
        pair.second = index;
        best_groups.push_back(pair);
    }

    int prevMin = -1;
    for(int i=1;i<D;i++){
        int min = prevMin>0?best_groups[0].first[i]:prevMin;
        if(best_groups.size()==1) break;
        prevMin = -1;
        for(int j=0;j<best_groups.size();j++){
            if(best_groups[j].first[i]>min){
                best_groups.erase(best_groups.begin()+j);
                j--;
            }else if(best_groups[j].first[i]<min){
                prevMin = best_groups[j].first[i];
                i--;
                break;
            }
        }
    }

    cout << best_groups[0].second + 1<<endl;
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
*/
