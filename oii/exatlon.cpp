#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#define MAX 1001
#define WINS_RED 1
#define WINS_BLUE 2
#define DRAW 0
#define RED 'R'

using namespace std;

int N, i, j;
char board[MAX][MAX];
int red[MAX][MAX], blue[MAX][MAX];
int tmp[MAX];
int area_red = 0, area_blue = 0;

int main(void) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> N;
	for (i = 0; i < N; i++) cin >> board[i];

	for (i = 0; i < N; i++)
		for (j = N-1; j >= 0; j--)
			if (board[i][j] == 'R') red[i][j] = red[i][j + 1] + 1;
			else blue[i][j] = blue[i][j + 1] + 1;

	//red
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			tmp[j] = red[j][i];

		sort(tmp, tmp + N);	//ordine crescente (0...N)

		for (j = N - 1; j >= 0 && tmp[j]; j--)
			area_red = max(area_red, tmp[j] * (N - j));
	}
	
	//blue
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			tmp[j] = blue[j][i];

		sort(tmp, tmp + N);	//ordine crescente (0...N)

		for (j = N - 1; j >= 0 && tmp[j]; j--)
			area_blue = max(area_blue , tmp[j] * (N - j));
	}

	if (area_red > area_blue)
		cout << WINS_RED << " " << area_red;
	else if (area_blue > area_red)
		cout << WINS_BLUE << " " << area_blue;
	else
		cout << DRAW << " " << area_red;

	return 0;
}