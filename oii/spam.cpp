#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
	//TRICK: bad and legitimate words can be the same...
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	set<string> set_badwords;
	set<string> set_legitimatewords;
	int badwords_number, legitimatewords_number, inbox;
	int spam, legitimate;
	spam = legitimate = 0;

	//reading bad words, put them in set
	cin >> badwords_number;
	for (int i = 0; i < badwords_number; i++)
	{
		string tmp;
		cin >> tmp;
		set_badwords.insert(tmp);
	}

	//reading legitimate words, put them in set
	cin >> legitimatewords_number;
	for (int i = 0; i < legitimatewords_number; i++)
	{
		string tmp;
		cin >> tmp;
		set_legitimatewords.insert(tmp);
	}

	//cicly reading each email sequentially
	cin >> inbox;
	for (int i = 0; i < inbox; i++)
	{
		bool isbad, islegitimate;
		int tmp_emailwords;
		isbad = islegitimate = false;
		cin >> tmp_emailwords;
		
		for (int j = 0; j < tmp_emailwords; j++)
		{
			string tmp;
			cin >> tmp;
			
			if (set_badwords.find(tmp) != set_badwords.end())
				isbad = true;

			if (set_legitimatewords.find(tmp) != set_legitimatewords.end())
				islegitimate = true;
		}

		if (isbad && !islegitimate)
			spam++;
		else if (!isbad && islegitimate)
			legitimate++;
	}

	cout << spam << " " << legitimate << endl;
	return 0;
}