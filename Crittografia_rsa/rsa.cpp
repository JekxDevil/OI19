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

//(A + B) mod M = (A mod M + B mod M) mod M
//(A · B) mod M = (A mod M · B mod M) mod M
void decifra(int N, int d, int L, int* messaggio, char* plaintext)
{	
	//TODO: when powera == powerb, then A == B. else B == A*cripto

	long int A, B;
	int power_a, power_b, cripto;
	bool isOdd;

	isOdd = d % 2 == 1 ? true : false;
	power_a = d >> 1;
	power_b = isOdd ? power_a + 1 : power_a;

	//itering through cripto numbers
	for(int i=0; i<L; i++){
		A = 1;
		B = 1;
		cripto = messaggio[i];
		bool isPowerBTurn;

		//creating variable A and B for the property (A mod M · B mod M) mod M 
		for(int num_potenza = 0, isPowerBTurn = false; num_potenza < d; num_potenza++){
			
			if(isPowerBTurn){
				B = B % N * cripto % N;
			} else {

				if(num_potenza < power_a){
					A = A % N * cripto % N;
				} else {
					isPowerBTurn = ~isPowerBTurn;
					B = B % N * cripto % N;
				}
			}
		}

		//decrypted char assignment
		plaintext[i] = A % N * B % N;
	}

	plaintext[L] = '\0';
}