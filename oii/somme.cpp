#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

int n, i, tmp;
priority_queue<int, vector<int>, greater<int>> numbers;
long long somma = 0;

int main(void) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> tmp;
		numbers.push(tmp);
	}

	while(numbers.size() > 1) {
		tmp = numbers.top();
		numbers.pop();
		tmp += numbers.top();
		numbers.pop();
		somma += tmp;
		numbers.push(tmp);
	}
	cout << somma << endl;
	return 0;
}