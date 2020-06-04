#define _CTR_NO_SECURE_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct sUser {
	string name;
	int total_posts;
	vector<sPost> vectorPosts;
	double words_average;
	int received_likes;
	int given_likes;
};

struct sPost {
	vector<string> vectorText;
	vector<string> vectorFollowers;
};

vector<string> split(string s, string delimiter);
double words_average(vector<sPost> *_vectorposts);
int received_likes(vector<sPost> *_vectorposts);
int given_likes(vector<sUser> *_vectorusers, string *_name);

int main(void) {
	//files
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	queue<int> results;
	string tmpnames, tmptext;
	int testcases, total_users, index;

	cin >> testcases;
	for (int i = 0; i < testcases; i++) {
		cin >> total_users;
		vector<sUser> vectorUsers;

		for (int j = 0; j < total_users; j++)
			cin >> vectorUsers[j].name;

		for (int j = 0; j < total_users; j++)
			cin >> vectorUsers[j].total_posts;

		for (int j = 0; j < total_users; j++) {
			
			for (int z = 0; z < vectorUsers[j].total_posts; z++) {
				getline(cin, tmptext);
				vectorUsers[j].vectorPosts[z].vectorText = split(tmptext, " ");
				getline(cin, tmpnames);
				vectorUsers[j].vectorPosts[z].vectorFollowers = split(tmpnames, " ");
			}
		}

		//assign indices
		for (int j = 0; j < total_users; j++) {
			vectorUsers[j].words_average = words_average(&vectorUsers[j].vectorPosts);
			vectorUsers[j].received_likes = received_likes(&vectorUsers[j].vectorPosts);
			vectorUsers[j].given_likes = given_likes(&vectorUsers, &vectorUsers[j].name);
		}

		//find the most famous

	}

	index = 1;
	while (!results.empty()) {
		cout << "Case #" << index++ << ": " << results.front() << endl;
		results.pop();
	}

	return 0;
}

double words_average(vector<sPost> *_vectorposts) {
	//return (split(_line, " ")).size();
}

int received_likes(vector<sPost> *_vectorposts) {
	/*for (sPost post : vectorUsers[j].vectorPosts)
		for (string like : post.vectorFollowers)
			args_received_likes.push_back(like);*/
}

int given_likes(vector<sUser> *_vectorusers, string *_name) {
	//arguments
	int user_likes = 0;

	for (sUser user : *_vectorusers) {
		if (user.name != *_name) {
			for (sPost post : user.vectorPosts)
				for (string like : post.vectorFollowers)
					if (like == *_name)
						user_likes++;
		}
	}
}

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}