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

int quadri(int N, long long M, int* V)
{
	//inizializzazioni int64
    long long length = 1, sum = 0;

    //avanzare per partire dal massimo in giu'
    for(; length<=N; length++){
        sum+=V[length-1];

        if(sum>M){
	    	length--;
            break;
		}
    }

    //lunghezza massima uguale array o 0 possibili contenuti
    if(length-1 == N)
        return N;
    else if(length == 0)
		return 0;

    //retrocedere
    bool found;

    //iterare diminuendo lunghezza a ogni ciclo
    for(long long spanLimit=N-length;length>0;length--, spanLimit++){
        found = true;

		//sommiamo tutte le possibili combinazioni di della lunghezza attuale
		for(long long pivot=0; pivot<=spanLimit; pivot++){
			for(long long span=0; span<=spanLimit; span++){
				sum = V[pivot];
				
				for(long long slider=pivot+span+1; slider-pivot<length; slider++){
					sum += V[slider];
				}

				//array cattivo, esci e diminuisci lunghezza
				if(sum>M){
					found=false;
					break;
				}
			}	

			//se un caso eccede, si esce dal ciclo e si diminuisce la lunghezza
			if(!found){
				break;
			}
		}
	
		//se tutti i casi buoni, massimale trovato, esco da ciclo
		if(found){
			return length;
		}
    }   

    return length;
}

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
