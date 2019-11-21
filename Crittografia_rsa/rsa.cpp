#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int d;
static int L;
static int* messaggio;
static char* plaintext;

// Declaring functions
void decifra(int N, int d, int L, int* messaggio, char* plaintext);

int main() {
	fr = stdin;
	fw = stdout;

	// Iterators used in for loops
	int i0;

	// Reading input
        fscanf(fr, "%d %d %d", &N, &d, &L);
	messaggio = (int*)malloc(100 * sizeof(int));
	plaintext = (char*)malloc(110 * sizeof(char));
	for (i0 = 0; i0 < L; i0++)
            fscanf(fr, "%d", &messaggio[i0]);

	// Calling functions
	decifra(N, d, L, messaggio, plaintext);

	// Writing output
        fprintf(fw, "%s\n", plaintext);
	
	fclose(fr);
	fclose(fw);
	return 0;
}

void decifra(int N, int d, int L, int *messaggio, char *plaintext) {
    // DATI:
    // N -> modulo
    // d -> esponente di c (char)
    // L -> lunghezza messaggio
    // EVITO BUFFER OVERFLOW:
    // (A+B) mod M = (A mod M + B mod M) mod M
    // (A*B) mod M = (A mod M * B mod M) mod M
    // carattere di fine stringa in plaintext[1]. (\n)
    
    for(int i=0; i<=L; i++)
    {
        int _iDecifrato = messaggio[i];

        for(int p=1; p<d; p++)
            _iDecifrato *= messaggio[i];

        _iDecifrato = _iDecifrato % N;
    }

    plaintext[L] = '\n';
}