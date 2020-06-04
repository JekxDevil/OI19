#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define NUMBERS 10

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int contacts_number;
	vector<string> vect_msgs;
	unordered_map<string, int> dict_numbers;
	cin >> contacts_number;

	//get encrypted contacts numbers
	for (int i = 0; i < contacts_number; i++)
	{
		string tmp;
		cin >> tmp;
		vect_msgs.push_back(tmp);
	}

	//get number encrypted conversion
	for (int i = 0; i < NUMBERS; i++)
	{
		string tmp;
		cin >> tmp;
		dict_numbers[tmp] = i;
	}

	//analize each contact number
	for (int i = 0; i < contacts_number; i++)
	{
		//index to track number decrypted position, j as index through message, txt as tmp string
		int index, j;
		string txt = "";
		index = j = 0;

		//analyze the whole contact number
		while (j < vect_msgs[i].size())
		{
			txt += vect_msgs[i][j];
			unordered_map<string, int>::iterator it = dict_numbers.find(txt);
			j++;

			if (it != dict_numbers.end())
			{
				vect_msgs[i].replace(index, txt.size(), to_string(dict_numbers[txt]));
				j = ++index;
				txt = "";
			}
		}

	}

	//print decrypted contacts
	for (int i = 0; i < contacts_number; i++)
		cout << vect_msgs[i] << endl;

	return 0;
}