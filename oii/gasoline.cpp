#include <iostream>
#include <vector>
using namespace std;

int main(void) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N, tmp;	//gas station
	long long total;
	
	cin >> N;
	int cost[N];
	int need[N];
	
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		cost[i] = tmp;
	}
	
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		need[i] = tmp;
	}
	
	int best = 100000;
	total = 0;
	for (int i = 0; i < N; i++) {
		if (best > cost[i]) {
			best = cost[i];
		}
		
		total += (long long int)(need[i] * best);
	}
	
	cout << total << endl;
	return 0;
}