#include<bits/stdc++.h>
using namespace std;


struct city{
	string name;
	int x;
	int y;
	float controls;
};

float findSize(city a, city b, city c){
	float area = ((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y))/2.0;
	return (area>0.0)?area:-area;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	vector<city> cities;
	int m,n; cin >> m >> n;
	for(int i=0;i<m;i++){
		string name;
		int x,y;
		cin >> name >> x >> y;
		city c;
		c.name = name;
		c.x = x;
		c.y = y;
		c.controls = 0.0;
		cities.push_back(c);
	}
	for(int i=0;i<n;i++){
		int a,b,c; cin >> a >> b >> c;
		if(a>m || b>m || c>m) continue;
		float size = findSize(cities[a-1],cities[b-1],cities[c-1]);
		cities[a-1].controls+=size;
		cities[b-1].controls+=size;
		cities[c-1].controls+=size;
	}
	float maxSize = INT_MIN;
	vector<string> best_cities;
	for(int i=0;i<m;i++){
		if(cities[i].controls>maxSize){
			best_cities.clear();
			best_cities.push_back(cities[i].name);
			maxSize = cities[i].controls;
		}else if(cities[i].controls==maxSize){
			best_cities.push_back(cities[i].name);
		}
	}
	sort(best_cities.begin(), best_cities.end());
	for(string x : best_cities) cout << x << endl;
	return 0;
}

