#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <queue>
#include <vector>

using namespace std;

// constraints
#define MAXN 1000000

// input data
int N, i, j, f, persona, ordini = 0;
int cerchia_amici[MAXN], contatore_portata[MAXN];
queue<int> coda;
vector<vector <int>> influenzati;	//vettore di vettore di interi


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
    assert(1 == scanf("%d", &N));
	influenzati.resize(N);

	for (i = 0; i < N; i++)
	{
		assert(2 == scanf("%d %d", &cerchia_amici[i], &contatore_portata[i]));

		for (j = 0; j < cerchia_amici[i]; ++j)
		{
			assert(1 == scanf("%d", &f));
			influenzati[f].push_back(i);
		}
    }

	for (i = 0; i < N; i++)
		if (contatore_portata[i] == 0)
			coda.push(i);

	ordini = coda.size();

	while (!coda.empty())
	{
		persona = coda.front();
		coda.pop();

		for (int influenzato : influenzati[persona])
		{
			contatore_portata[influenzato]--;

			if (contatore_portata[influenzato] == 0)
			{
				coda.push(influenzato);
				ordini++;
			}
		}

	}

    printf("%d\n", ordini); // print the result
    return 0;
}
