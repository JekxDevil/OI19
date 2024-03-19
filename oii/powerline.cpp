#include <stdio.h>
#include <assert.h>
#include <algorithm>

using namespace std;

// constraints
#define MAXN 100000

// input data
int N, i;
int A[MAXN];

int main() {
//  uncomment the following lines if you want to read/write from files
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &N));
    for(i=0; i<N; i++)
        assert(1 == scanf("%d", &A[i]));

    int pos = N-1, val = A[N-1], sol = 0;
    
    //ciclo al contrario dell'array torri
	for (i = N-1; i >= 0; i--) {
		//quando valore incontra elemento minore o uguale a lui
		//aggiorna valore e indice
        if (val <= A[i]) {
            val = A[i];
            pos = i;
        }
        
        //il risultato e' dato dal massimo tra
        //la differenza 
        sol = max(sol, pos - i);
    }

    printf("%d\n", sol); // print the result

    return 0;
}