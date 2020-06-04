#include <iostream>

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N, max, min;
	cin >> N;
	char boxes[N];
	
	for(int i = 0; i < N; i++)
		cin >> boxes[i];
	
	max = N;
	min = 1;
	
	for(int i = 0; i < N; i++)
		if(boxes[i] == '<') cout << min++ << " ";
		else cout << max-- << " ";
	
	return 0;
}
