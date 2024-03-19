#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define OUTRANGE 50001

using namespace std;

struct Gallery {
	long d;
	long brightness;
};

int main() {
	// files
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	// variables
	vector<vector<Gallery>> graph;
	vector<bool> track(OUTRANGE, false);
	int gates, galleries, harmony, spike;
	int counter = 0;

	cin >> gates >> galleries >> harmony >> spike;
	//cout << gates << galleries << harmony << spike << endl;
	
	graph.resize(gates+1);
	Gallery arc;
	long tmp;
	for (int i = 0; i < galleries; i++) {
		cin >> tmp;
		cin >> arc.d >> arc.brightness;
		//cout << tmp << arc.d << arc.brightness << endl;
		graph[tmp].push_back(arc);
		graph[arc.d].push_back({tmp, arc.brightness});
	}

	/*cout << endl;
	cout << "nodi" << endl;
	for (int i = 0; i < galleries; i++)
		for(Gallery g : graph[i])
			cout << i << g.d << g.brightness << endl;
	cout << endl;*/

	Gallery chosen;
	while (harmony != spike) {
		track[harmony] = true;
		chosen = {0, OUTRANGE};
		for (Gallery g : graph[harmony])
		{
			if (g.brightness < chosen.brightness)
				chosen = g;
		}

		if (chosen.brightness == OUTRANGE || track[chosen.d]) {
			counter = -1;
			harmony = spike;
		} else {
			counter++;
			harmony = chosen.d;
		}

	}

	cout << counter << endl;
	return 0;
}
