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

int calculateVariation(vector<int> sched, int index, int D){
    int variation = 0;
    for(int i=index+1;i<index+D;i++){
        variation+=abs(sched[i]-sched[i-1]);
    }
    return variation;
}

int solve(){
    cin >> D >> N;
    int tmp;
    for(int i = 0; i < N; i++){
        cin >> tmp;
        sched.push_back(tmp);
    }
    if(N==0 || D==0 || D > N){
        return -1;
    }else if(D==N) {
        return 1;
    }
    int best_max = 1000000;
    int best_sum = 1000000;
    vector<int> best_group_indexes;
    for(int i=0;i<N-D+1;i++){
        int temp_max,temp_sum;
        temp_max = temp_sum = 0;
        if(sched[i]>best_max) continue; // if the first value of the array is bigger than the best max, it wont be the best max aka skip
        for(int j=i;j<i+D;j++){
            temp_sum += sched[j];
            if(sched[j]>temp_max) temp_max = sched[j];
        }
        if(temp_max < best_max){
            best_group_indexes.clear();
            best_max = temp_max;
            best_sum = temp_sum;
            best_group_indexes.push_back(i);
        }else if(temp_max == best_max){
            if(temp_sum < best_sum){
                best_sum = temp_sum;
                best_group_indexes.clear();
                best_group_indexes.push_back(i);
            }else if(temp_sum == best_sum){
                best_group_indexes.push_back(i);
            }
        }
    }
    if(best_group_indexes.size()==0) return best_group_indexes[0]+1;
    if(best_sum == 0) return best_group_indexes[0]+1;

    int best_index = best_group_indexes[0];
    vector<int> best_array = {sched.begin()+best_group_indexes[0],sched.begin()+best_group_indexes[0]+D};
    sort(best_array.begin(), best_array.end(), greater<int>());

    for(int i : best_group_indexes){
        vector<int> v = {sched.begin()+i,sched.begin()+i+D};
        sort(v.begin(),v.end(),greater<int>());
        bool better = false;
        for(int j=0;j<D;j++){
            if(v[j]>best_array[j]){
                better = false;
                break;
            }
            if(v[j]<best_array[j]) better = true;
        }
        if(better){
            best_array = v;
            best_index = i;
        }
    }

    return best_index+1;
}

int main(){
    int result = solve();
    if(result==-1){
        cout << "impossible" << endl;
    }else{
        cout << result << endl;
    }
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
