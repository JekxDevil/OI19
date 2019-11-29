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
    /*  DISPOSIZIONI:
        Tantissima RAM. Pochissimo tempo. Come sprecare il piu' possibile la ram? Come rendere il codice piu' veloce possibile?
    */

    long long length = 0, sum = 0;

    //avanzare per partire dal massimo in giu'
    for(; length<N; length++){
        sum+=V[length];
        if(sum>M){
	    length--;	
            break;
	}
    }

    //lunghezza massima uguale array o 0 possibili contenuti
    if(length == N)
        return length;
    else if(length <= 0)
	return 0;

    //retrocedere
    bool found;

    //iterare diminuendo lunghezza a ogni ciclo
    for(long long _spanLimit=0;length>0;length--, _spanLimit++){
	//printf("\n [Entro dentro ciclo tosto] \n");
	//diamo per scontato che ogni ciclo sia il massimo ottenibile
        found = true;

	//sommiamo tutte le possibili combinazioni di della lunghezza attuale
	for(long long pivot=0; pivot<_spanLimit+1; pivot++){
	    for(long long span=0; span<_spanLimit+1; span++){
	        sum = V[pivot];
	        
		for(long long slider=pivot+span+1; slider<N && slider-pivot<length; slider++){
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
	   // printf("break caso buono: length = %d \n",length);
	    break;
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
