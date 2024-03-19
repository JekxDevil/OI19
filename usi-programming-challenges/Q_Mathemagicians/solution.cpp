#include<bits/stdc++.h>
using namespace std;

int N;
string real_str;
string happy;

int switches(string s) {
	int count = 1;
	for(int i=1; i<s.length(); i++) {
		count += s[i] != s[i-1];
	}
	return count - (count % 2 == 1);
}

bool has_adjacent(string s) {
	if (s[0] == s[s.length()-1]) return true;
	for (int i=1;i<s.length();i++) {
		if (s[i] == s[i-1]) return true;
	}
	return false;
}

bool solve() {
	cin >> N >> real_str >> happy;
	if (real_str == happy) return true;
	
	int real_str_switches = switches(real_str);
	int happy_switches = switches(happy);
	
	if (real_str_switches <= 1) return false;
	return (real_str_switches > happy_switches)
		|| (real_str_switches == happy_switches	&& has_adjacent(happy));
}

int main() {
	bool ans = solve();
	if (ans) cout << "yes" << endl;
	else cout << "no" << endl;
	return 0;
}
