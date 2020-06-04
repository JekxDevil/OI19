#include <iostream>

using namespace std;

bool is_prime(int n){
	for(int i = 2; i < n/2; i++)
		if(n % i == 0)
			return false;
			
	return true;
}

bool is_semiprime(int& n, int& f1, int& f2){
	int mid = n/2;
	
	for(int i = 2; i < mid; i++)
		if(n%i == 0)
			if(is_prime(i) && is_prime(n/i)){
				f1 = i;
				f2 = n/i;
				return true;
			}
				
	return false;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, f1, f2;
	cin >> n;
	
	if((n&1) && is_semiprime(n, f1, f2))
		cout << f1 << " " << f2 << endl;
	else
		cout << -1 << endl;
	
	return 0;
}
