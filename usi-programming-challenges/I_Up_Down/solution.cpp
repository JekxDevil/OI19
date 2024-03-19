#include<bits/stdc++.h>
using namespace std;

void solve(){
	int N,P,V; cin >> N >> P >> V;
	int S[N];
	vector<int> peaks,valleys;
	int npeaks,nvalleys;
	npeaks = nvalleys = 0;
	for(int i=0;i<N;i++){
	 	cin >> S[i];
		if(i<2) continue;
		if(S[i]-S[i-1]>0 && S[i-1]-S[i-2]<0) valleys.push_back(i-1);
		if(S[i]-S[i-1]<0 && S[i-1]-S[i-2]>0) peaks.push_back(i-1);
	}
	for(int pp : peaks){
		int i,j;
		i=j=0;
		bool toAdd = true;
		while(i<P-1&&toAdd){
			i++;
			j++;
			if(pp-i<0 || pp+j>=N){
				toAdd=false;
				continue;
			}
			toAdd = !(S[pp-i+1]-S[pp-i]<0 || S[pp+j-1]-S[pp+j]<0);
		}
		npeaks+=toAdd;
	}
	for(int pp : valleys){
		int i,j;
		i=j=0;
		bool toAdd = true;
		while(i<V-1&&toAdd){
			i++;
			j++;
			if(pp-i<0 || pp+j>=N){
				toAdd=false;
				continue;
			}
			toAdd = !(S[pp-i+1]-S[pp-i]>0 || S[pp+j-1]-S[pp+j]>0);
		}
		nvalleys+=toAdd;
	}
	cout << npeaks << " " << nvalleys << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
	return 0;
}

