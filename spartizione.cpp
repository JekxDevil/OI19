#include <iostream>

using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int totos, amount, gems, partners_number;
	cin >> gems >> partners_number;
	partners_number--;	//excluding toto
	amount = 1;		//initialize the first divide
	totos = 0;		//important because before was an undefined value
	
	//until there are gems left
	while(gems > 0){
		
		if(gems >= amount){
			totos += amount;
			gems -= amount++;
		}else{
			totos += gems;
			gems ^= gems;
		}
		
		gems -= partners_number;
	}
	
	cout << totos;
	return 0;
}
