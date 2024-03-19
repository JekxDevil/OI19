#include<bits/stdc++.h>
using namespace std;

int round(int price) {
	if (price % 10 < 5) {
		return price - price%10;
	}
	return price + (10 - (price % 10));
}

int N,D;
vector<int> prices;
int cache[2001][21];


int main() {
	cin >> N >> D;
	
	for(int i=0;i<2001;i++) {
		for(int j = 0; j < 21; j++) {
			cache[i][j] = 0;
		}
	}

	prices = vector<int>(N);
	for(int i=0;i<N;i++) cin >> prices[i];
	
	int sum = 0;
	for(int i=N-1;i>=0;i--) {
		sum += prices[i];
		cache[i][0] = round(sum);
	}

	for(int i=1; i<=D; i++) {
		for(int j=0; j<=N; j++) {
			int sum = 0;
			cache[j][i] = INT_MAX;
			for(int k=j; k<=N; k++) {
				cache[j][i] = min(cache[j][i], round(sum) + cache[k][i-1]);
				sum+=prices[k];
			}
		}
	}
	
	cout << cache[0][D] << "\n";
	return 0;
}
