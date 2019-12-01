#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static FILE *fr, *fw;

// Declaring variables
static int N;
static long long M;
static int* V;
static int B;

// Declaring functions
int quadri(int N, long long M, int* V);

int main() {
	fr = stdin;
	fw = stdout;

	// Iterators used in for loops
	int i0;

	// Reading input
	fscanf(fr, "%d %lld", &N, &M);
	V = (int*)malloc(N * sizeof(int));
	for (i0 = 0; i0 < N; i0++)
    	{
	    fscanf(fr, "%d", &V[i0]);
	}

	// Calling functions
	B = quadri(N, M, V);

	// Writing output
	fprintf(fw, "%d\n", B);

	fclose(fr);
	fclose(fw);
	return 0;
}

int quadri(int N, long long M, int V[]){
    long long sum = 0;
    long long range = 0;

    //range massimo ottenibile dalla somma cumulativa minore di M
    for (range = 0; range < N; range++) {
        sum += V[range];

        if (sum > M) {
            range--;
            break;
        }
    }

    //se range sfora senza intoppi allora la lunghezza e' uguale a N
    if (range == N) {
        return range;
    }

    long long s = 0;    //somma totale del range massimo
    for (long long j = 0; j < range+1; j++) {
        s += V[j];
    }

    //z = range < z < N
    for (long long z = range+1; z < N; z++) {
        s = s - V[z-(range+1)] + V[z];      //stracazzo di sostituzione

        while (s > M && range >= 0) {       //fintanto che la somma e' maggiore di massimale e range positivo
            s -= V[z-range];    //elimino numero a sinistra dalla somma range e diminuisco range
            range -= 1;
        }

        if (range == 0) break;  //qualore range raggiunge 0, ritornalo
    }

    return range+1;
}
