#include<bits/stdc++.h>
#define roundz(x,d) ((floor(((x)*pow(10,d))+.5))/pow(10,d))
using namespace std;

struct city{
	string name;
	int x;
	int y;
};

float findSize(city a, city b, city c){
	float area = ((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y))/2.0;
	return (area>0.0)?area:-area;
}

void string_lower(string& data){
	std::for_each(data.begin(), data.end(), [](char & c) {
  	c = ::tolower(c);
	});	
}

bool comp(string s1, string s2){
	string_lower(s1);
	string_lower(s2);
	return s1.compare(s2)<0;
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
		cities.push_back(c);
	}
	vector<float> areas = vector<float>(m,0.0);
	for(int i=0;i<n;i++){
		int a,b,c; cin >> a >> b >> c;
		float size = findSize(cities[a-1],cities[b-1],cities[c-1]);
		size = roundz(size, 3);
		areas[a-1]+=size;
		areas[b-1]+=size;
		areas[c-1]+=size;
	}
	float maxSize = INT_MIN;
	vector<string> best_cities;
	for(int i=0;i<m;i++){
		if(areas[i]>maxSize){
			best_cities.clear();
			best_cities.push_back(cities[i].name);
			maxSize = areas[i];
		}else if(areas[i]==maxSize){
			best_cities.push_back(cities[i].name);
		}
	}
	sort(best_cities.begin(), best_cities.end(), comp);
	for(string x : best_cities) cout << x << endl;
	return 0;
}

