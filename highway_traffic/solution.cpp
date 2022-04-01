#include<bits/stdc++.h>
using namespace std;

struct point{
	int x;
	char type;
};

bool comparePoint(point p1, point p2){
	return p1.x<p2.x;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int N;
	cin >> N;

	char type;
	int x;
	vector<point> points;
	vector<pair<int,int>> intervals;
	for(int i=0;i<N;i++){
		cin >> type >> x;
		int k = (type=='C')?50:100;
		int start,end;
		start = x-k;
		end = x+k;
		point p1,p2;
		p1.x = start;
		p1.type = 's';
		p2.x = end;
		p2.type = 'e';
		points.push_back(p1);
		points.push_back(p2);
	}

	sort(points.begin(), points.end(), comparePoint);

	int counter = 0;

	pair<int,int> current;
	for(point p : points){
		cout << "x: " << p.x << " counter: " << counter << endl;
		if(p.type=='e'){
			if(counter==3){
				current.second = p.x;
				intervals.push_back(current);
			}
			counter-=1;
		}else{
			if(counter==2){
				current.first = p.x;
			}
			counter+=1;
		}
	}

	for(int i=1;i<intervals.size();i++){
		if(intervals[i].first == intervals[i-1].second){
			pair<int,int> new_intv;
			new_intv.first = intervals[i-1].first;
			new_intv.second = intervals[i].second;
			intervals.erase(intervals.begin()+i);
			intervals.erase(intervals.begin()+i-1);
			i--;
			intervals.insert(intervals.begin()+i,new_intv);
			i--;
		}
	}
	
	for(pair<int,int> p : intervals){
		if(p.first != p.second) cout << p.first << " " << p.second << endl;
	}

	return 0;
}

