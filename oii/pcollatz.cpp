	#include <iostream>
	
	using namespace std;
	
	int collatz(int n){
		
		int length = 1;
		
		//finche' n diverso da 1
		while(n > 1){
			
			length++;
			if(n % 2 == 0){
				//se n e' pari
				n >>= 1;
			}else{
				//se n e' dispari	
				n *= 3;
				n++;
			}
		}
		
		return length;
	}
	
	int pollatz(int n, int collatz_result){
		
		int length = 1;
		
		//finche' n diverso da 1
		while(n > 1 && length < collatz_result){
			
			length++;
			if(n % 2 == 0){
				//se n e' pari
				n >>= 1;
			}else{
				//se n e' dispari	
				n *= 5;
				n++;
			}
		}
		
		return length;
	}
	
	int main(){
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		
		int a, b, pollatz_better;
		cin >> a >> b;
		pollatz_better = 0;
		
		for(int i = a; i <= b; i++){
			
			int collatz_result = collatz(i);
			int pollatz_result = pollatz(i, collatz_result);
			
			if(pollatz_result < collatz_result)
				pollatz_better++;
		}
		
		cout << pollatz_better << endl;
		return 0;
	}