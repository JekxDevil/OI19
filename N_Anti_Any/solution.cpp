#include<bits/stdc++.h>
using namespace std;

int to_decimal(string s){
	return stoi(s, 0, 2);
}

const long MOD = 1e9+7;
void solve(){
	int N; cin >> N;
	string k; cin >> k;
	int kl = k.length();

	if(N < kl){
		cout << (1<<N) << endl;
		return;
	}

	if(kl == 1){
		cout << 1 << endl;
		return;
	}

	int v_l = kl-1; // the length of the element of each array
	int v_n = 1<<v_l; // the number of possible combinations with length v_l
	int vals[2][v_n];

	for(int i=0;i<v_n;i++){
		vals[0][i] = 1;
		vals[1][i] = 0;
	}

	int avoid = to_decimal(k);
	int n = kl;

	int new_idx;
	while(n<=N){
		for(int i=0;i<2;i++){ // i is the number im adding in front
			for(int j=0;j<v_n;j++){
				new_idx = (i<<v_l)+j;
				if(new_idx!=avoid){
					new_idx = new_idx>>1;
					vals[1][new_idx] += vals[0][j];
					vals[1][new_idx] = vals[1][new_idx] % MOD;
				}
			}
		}
		for(int i=0;i<v_n;i++){
			vals[0][i] = vals[1][i];
			vals[1][i] = 0;
		}
		n++;
	}
	int sum = 0;
	for(int i=0;i<v_n;i++){
		sum+=vals[0][i];
		sum = sum % MOD;
	}
	cout << sum << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	for(int t=1;t<=T;t++){
		solve();
	}
	return 0;
}

