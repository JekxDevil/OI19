#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

#define MAXN 10000

int decipher(int N, int D, char** strings){
	int arrayInt[N][D];
	int arrayDifference[N];
	int _iMax = 1;

    //get ascii char values
	for(int i = 0; i < N; i++){
		for(int j = 0; j < D; j++){
			arrayInt[i][j] = ((int)strings[i][j]) - 96;
		}
	}

    //find number of matches
	for(int i=0; i<N-1; i++){
        arrayMatches[i] = 1;        //each string match itself

        for(int j=i+1; j<N; j++){
            bool arrayIsEqual[D-1];     //to track matchability of strings

            for(int k=0; k<D-1; k++){
                //if there are no differences between the char value difference,
                //the two characters has the same caesar cipher key value
                if((arrayInt[i][k+1] - arrayInt[i][k]) == (arrayInt[j][k+1] - arrayInt[j][k])){
                    arrayIsEqual[k] = true;
                } else {
                    arrayIsEqual[k] = false;
                }
            }

            //if the strings were equal, increment the match value
            bool _bEquals = true;

            for(int l=0; l<D-1; l++){
                if(arrayIsEqual[l] == false)
                    _bEquals = false;
            }

            if(_bEquals)
                arrayMatches[i]++;
        }
	}

    //find max matches value
	for(int i=0; i<N; i++){
		if(arrayMatches[i] > _iMax)
			_iMax = arrayDifference[i];
	}

	return _iMax;
}

int main(){
	int N, D, i;
	char** strings;

	assert(2==scanf("%d %d", &N, &D));
	strings = (char**)malloc(N*sizeof(char*));

	for(i=0; i<N; i++){
		strings[i] = (char*)malloc((D+1)*sizeof(char));
		assert(1==scanf("%s", strings[i]));
	}

	printf("%d\n", decipher(N, D, strings));
	return 0;
}
