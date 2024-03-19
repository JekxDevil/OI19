#include <iostream>

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, length;
	cin >> n;
	length = 1;
	
	//while different to one
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
	
	cout << length << endl;
	return 0;
}
