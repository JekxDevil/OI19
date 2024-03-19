#include<bits/stdc++.h>
using namespace std;

struct city{
	float x;
	float y;
	string name;
	unordered_set<int> adj;
};

float getDeterminant(city n1, city c, city n2){
	float det = n1.x*(c.y-n2.y) - n1.y*(c.x - n2.x) + (c.x*n2.y - c.y*n2.x);
	return det;
}

void visit(int starting, vector<city> cities){
	int current = starting;
	int previous = -1;
	vector<int> visited;
	int min_index = 0;
	string min_name = "ZZZZZZZZZZ";
	while(current!=starting || previous==-1){
		visited.push_back(current);

		if(cities[current].name < min_name){
			min_index = visited.size()-1;
			min_name = cities[current].name;
		}

		int old_current = current;

		int next1 = *(cities[current].adj.begin());
		int next2 = *(++cities[current].adj.begin());

		if(next1==previous)
			current = next2;
		else if(next2==previous)
			current = next1;
		else{
			float det = getDeterminant(cities[next1], cities[current], cities[next2]);
			if(det>0){
				current = next2;
			}else if(det<0){
				current = next1;
			}else
				current = cities[next1].y < cities[next2].y ? next1 : next2;
		}
		previous = old_current;
	}

	for(int i=0;i<visited.size();i++){
		int index = (min_index + i)%visited.size();
		cout << cities[visited[index]].name << endl;
	}
}

void count(vector<city>& cities, int a, int b){
	if(a<b){
		count(cities,b,a);
		return;
	}
	if(cities[a].adj.find(b)!=cities[a].adj.end()){
		cities[a].adj.erase(b);
	}else{
		cities[a].adj.insert(b);
	}
	if(cities[b].adj.find(a)!=cities[b].adj.end()){
		cities[b].adj.erase(a);
	}else{
		cities[b].adj.insert(a);
	}
}

int main(){
	int m,n; cin >> m >> n;
	vector<city> cities;
	for(int i=0;i<m;i++){
		city c;
		cin >> c.name >> c.x >> c.y;
		cities.push_back(c);
	}
	for(int i=0;i<n;i++){
		int a,b,c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		count(cities,a,b);
		count(cities,b,c);
		count(cities,a,c);
	}
	int left_index = 0;
	for(int i=0;i<cities.size();i++){
		if(cities[i].x < cities[left_index].x) left_index = i;
	}
	visit(left_index, cities);	
	return 0;
}
