#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")

#define vec vector;
#define ll long long
#define ld long double
#define len(x) ((int)x.size())
#define all(a) a.begin(),a.end()
#define INF (int)1e9
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;

const int mod = 1e9+7;

void solve(){
	int N; cin >> N;
	int a,b,preva,prevb;
	a = b = 1;
	preva = prevb = 0;
	for(int i=0;i<N;i++){
		preva = a;
		prevb = b;
		preva = preva%mod;
		prevb = prevb%mod;
		a = preva + prevb;
		b = preva;

	}
	cout << a%mod << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	for(int t=1;t<=T;t++){
		cout << "Case #" << t << ": ";
		solve();
	}
	return 0;
}

