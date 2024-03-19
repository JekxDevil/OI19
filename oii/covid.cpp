#define _CTR_NO_SECURE_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct sNotorious {
	int person;
	int infection;
};

struct sPlace {
	int x;
	int y;
};

struct sHotSpot {
	int x;
	int y;
	int positives;
};

double get_distance(int x, int y, int a, int b);

int main(void) {
	//files
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int testcases, people, places, index;
	double distance, tmpdistance;
	sPlace place;
	sHotSpot hotspot;
	sNotorious notorious;
	vector<sPlace> vectorPeople;
	vector<sHotSpot> vectorHotSpots;
	queue<int> results;

	cin >> testcases;
	for (int i = 0; i < testcases; i++) {
		
		cin >> people;
		vector<int> compare(people, 0);
		for (int j = 0; j < people; j++) {
			cin >> place.x >> place.y;
			vectorPeople.push_back(place);
		}

		cin >> places;
		for (int j = 0; j < places; j++) {
			cin >> hotspot.x >> hotspot.y >> hotspot.positives;
			vectorHotSpots.push_back(hotspot);
		}

		cin >> distance;

		//all data retrieved
		for (int j = 0; j < vectorPeople.size(); j++) {
			
			place = vectorPeople[j];
			for (int z = 0; z < vectorHotSpots.size(); z++) {
				
				hotspot = vectorHotSpots[z];
				tmpdistance = get_distance(place.x, place.y, hotspot.x, hotspot.y);
				if (tmpdistance <= distance)
					compare[j] += hotspot.positives;
			}
		}

		//get most in risk person
		notorious.person = notorious.infection = 0;
		for (int j = 0; j < compare.size(); j++) {
			if (compare[j] > notorious.infection) {
				notorious.person = j + 1;
				notorious.infection = compare[j];
			}
		}

		compare.clear();
		vectorPeople.clear();
		vectorHotSpots.clear();
		results.push(notorious.person);
	}

	index = 1;
	while (!results.empty()) {
		cout << "Case #" << index++ << ": " << results.front() << endl;
		results.pop();
	}

	return 0;
}

double get_distance(int x, int y, int a, int b) {
	return sqrt(pow((x - a), 2) + pow((y - b), 2));
}