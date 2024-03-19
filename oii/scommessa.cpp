#include <iostream>
#include <fstream>
using namespace std;

const int MAX_N = 110;
int C[MAX_N];
int K[MAX_N];
bool parity[MAX_N];
int sx_even[MAX_N];
int sx_odd[MAX_N];
int N, amount;

int main(void) {
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	// input
	int tmp;
	in >> N;
	for(int i = 0; i < N; i++) {
		in >> tmp;
		C[i] = tmp;
		parity[i] = tmp & 1 ? false : true;
	}
	
	// mapping odd and even numbers
	if (parity[0]) sx_even[0] = 1;
	else sx_odd[0] = 1;
	
	for (int i = 1; i < N; i++) {
		sx_even[i] = sx_even[i-1] + parity[i];
		sx_odd[i] = sx_odd[i-1] + !parity[i];
	}
	
	for (int i = 0; i < N; i++)
		if (!(C[i] & 1) && sx_even[i-1] == sx_odd[i-1])
			K[amount++] = C[i];
	
	// output
	out << amount << endl;
	for (int i = 0; i < amount; i++)
		out << K[i] << " ";
	
	return 0;
}