#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

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

void decifra(int N, int d, int L, int* messaggio, char* plaintext)
{	
	unsigned long long int crypto, result;

	//itering through crypto numbers in array
	for(unsigned long long int index=0; index<L; index++){
			crypto = messaggio[index];
			result = 1;

			while(d > 0){

				//current odd exponential
				if(d & 1)
					result = result % N * crypto % N;

				crypto = crypto % N * crypto % N;
				d >>= 1;
			}

		//decrypted char assignment 
		plaintext[index] = result;
	}

	plaintext[L] = '\0';
}