#include<bits/stdc++.h>
using namespace std;

struct city{
	string name;
	float x;
	float y;
};

float calculateArea(city a, city b, city c){
	float area = ((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y))/2.0;
	return (area>0.0)?area:-area;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int m,n; cin >> m >> n;
	vector<city> cities;
	for(int i=0;i<m;i++){
		string name;
		float x,y;
		cin >> name >> x >> y;
		city c;
		c.name = name;
		c.x = x;
		c.y = y;
		cities.push_back(c);
	}
	vector<float> controlled = vector<float>(m,0.0);
	for(int i=0;i<n;i++){
		int a,b,c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		float area = calculateArea(cities[a], cities[b], cities[c]);
		controlled[a]+=area;
		controlled[b]+=area;
		controlled[c]+=area;
	}
	vector<string> best_cities;
	float bestArea=INT_MIN;
	for(int i=0;i<m;i++){
		if(controlled[i] == bestArea) best_cities.push_back(cities[i].name);
		else if(controlled[i]>bestArea){
			bestArea = controlled[i];
			best_cities.clear();
			best_cities.push_back(cities[i].name);
		}
	}
	sort(best_cities.begin(), best_cities.end());
	for(string x : best_cities) cout << x << endl;
	return 0;
}
