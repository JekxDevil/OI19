#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

// constraints
#define MAXN 120
#define MOD 1000000007

// input data
int N, X, possible_matches;
int board[MAXN + 1][MAXN + 1];
int sum_rows[MAXN + 1][MAXN + 1];
int sum_columns[MAXN + 1][MAXN + 1];
int memo[MAXN + 1][MAXN + 1][MAXN + 1][MAXN + 1];
bool only_positives;

void collecting_sums()
{
	for (int i = 1; i <= N; i++)
	{
		sum_rows[i][1] = board[i][1];
		sum_columns[1][i] = board[1][i];

		for (int j = 2; j <= N; j++)
		{
			sum_rows[i][j] = sum_rows[i][j - 1] + board[i][j];
			sum_columns[j][i] = sum_columns[j - 1][i] + board[j][i];
		}
	}
}

void fill_memo()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (board[i][j] >= X)
				memo[i][j][i][j] = 5;
			else
				memo[i][j][i][j] = 1;
}

void fill_memo_positives()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			memo[i][j][i][j] = 5;
}

int match_counter_positives(int r1, int c1, int r2, int c2)
{
	long long result = 0;

	//base case
	if (r1 > r2 || c1 > c2)
		return 1;
	
	if (memo[r1][c1][r2][c2])
		return memo[r1][c1][r2][c2];

	result += match_counter_positives(r1 + 1, c1, r2, c2) << 1;
	result += match_counter_positives(r1, c1 + 1, r2, c2) << 1;

	return memo[r1][c1][r2][c2] = (result + 1) % MOD;
}

int match_counter(int r1, int c1, int r2, int c2) 
{
	long long int top, bottom, left, right, result = 0;

	//base case
	if (r1 > r2 || c1 > c2)
		return 1;

	//memoization case A.x == B. 
	if (memo[r1][c1][r2][c2])
		return memo[r1][c1][r2][c2];

	//pensarci bene, manca qualcosa 1 4 11
	top = sum_rows[r1][c2] - sum_rows[r1][c1 - 1];
	bottom = sum_rows[r2][c2] - sum_rows[r2][c1 - 1];
	left = sum_columns[r2][c1] - sum_columns[r1 - 1][c1];
	right = sum_columns[r2][c2] - sum_columns[r1 - 1][c2];

	if (top >= X)
		result += match_counter(r1 + 1, c1, r2, c2);

	if (bottom >= X) 
		result += match_counter(r1, c1, r2 - 1, c2);

	if (left >= X)
		result += match_counter(r1, c1 + 1, r2, c2);

	if (right >= X)
		result += match_counter(r1, c1, r2, c2 - 1);

	return memo[r1][c1][r2][c2] = (result + 1) % MOD;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N, &X));
	only_positives = true;

    for(int i=1; i <= N; i++) 
		for (int j = 1; j <= N; j++)
		{
			assert(1 == scanf("%d", &board[i][j]));
			
			if (board[i][j] < 0)
				only_positives = false;
		}

	if (X == 0 && only_positives)
	{
		fill_memo_positives();
		possible_matches = match_counter_positives(1, 1, N, N);
	}
	else
	{
		collecting_sums();
		fill_memo();
		possible_matches = match_counter(1, 1, N, N);
	}

    printf("%d\n", possible_matches);
    return 0;
}
