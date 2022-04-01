#include<bits/stdc++.h>
using namespace std;

int f(string s, int n, string dw, int dwl){
	if(s.length()>=dwl && s.substr(s.length()-dwl) == dw) return 0;
	if(s.length()==n) return 1;
	return f(s+"0", n, dw, dwl) + f(s+"1", n, dw, dwl);
}

void solve(){
	int n; cin >> n;
	string s; cin >> s;
	cout << f("", n, s, s.length()) << endl;
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

