#include <stdio.h>
#include <vector>
using namespace std;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    register int i, N;    // number of ropes
    vector<int> P(100001, 0);    // ropes array connected to parent i
    vector<vector<int>> graph(100001);
    vector<int> maxTime(100001, 0);
    int total = total ^ total;
    int tmp = tmp ^ tmp;

    scanf("%d", &N);
    for (i = 0; i < N; i++) scanf("%d", &P[i]);
    for (i = 0; i < N; i++) {
        scanf("%d", &tmp);
        graph[P[i]].push_back(tmp);
    }

    int index = index ^ index;
    for (vector<int>& v : graph) {
        tmp = tmp ^ tmp;
        for (int& l : v) {
            maxTime[index] += l;
            if (l > tmp) tmp = l;
        }
        maxTime[index] -= tmp;
        index++;
    }

    for (i = 0; i < index; i++) total += maxTime[i];
    printf("%d\n", total);
    return 0;
}