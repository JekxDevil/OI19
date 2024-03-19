#define _CTR_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <set>
#include <iterator>
#include <queue>
#include <string>
#define BEGIN 11

using namespace std;

int main(void*){
	//files
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	long long testcases, visits, index;
	queue<long long> results;
	string name;
	set<string> monuments;
	cin >> testcases;

	for (long long i = 0; i < testcases; i++) {
		cin >> visits;
		getline(cin, name);
		monuments.clear();

		for (long long j = 0; j < visits; j++) {
			getline(cin, name);
			name = name.substr(BEGIN, (name.length() - BEGIN));
			monuments.insert(name);
		}

		results.push(monuments.size());
	}

	index = 1;
	while(!results.empty()){
		cout << "Case #" << index++ << ": " << results.front() << endl;
		results.pop();
	}

	return 0;
}