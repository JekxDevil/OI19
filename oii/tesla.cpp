#include <iostream>
#include <string>
#include <vector>
#define COST 10
using namespace std;

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int points, starting_index;
	vector<int> trip;
	vector<long long> energy_mapped;
	int tmp;
	
	cin >> points;
	for(int i = 0; i < points; i++)
	{
		cin >> tmp;
		trip.push_back(tmp);
	}
	
	for(int i = 0; i < points; i++)
	{
		tmp = 0;
		for(int j = 0; j <= i; j++)
		{
			tmp += trip.at(j);
		}
		
		energy_mapped.push_back(tmp);
	}
	
	for(int i = starting_index = tmp = 0; i < points; i++)
	{
		tmp += trip[i] - COST;
		
		if(tmp < 0)
			tmp -= energy_mapped[starting_index++];
	}
	
	cout << ++starting_index << endl;
	
	return 0;
}
