#include <stdio.h>
#include <assert.h>

// constraints
#define MAXL 100000

// input data
char identifier[MAXL + 1];

int main() {
    long long result = 0, index = 0;
    bool isShortComment = false, isLongComment = false, slashFlag = false, asteriscFlag = false, isString = false, isNewWord = false, isMacro = false, isCorrect = false;

    //  uncomment the following lines if you want to read/write from files
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    assert(1 == scanf("%s", identifier));
    char c;
    
    //ascii reading
    while ((c = getchar()) != EOF) {
//problemi con 2 testcase. asterisco o comunque operazioni con variabili
        if(isCorrect) {
            index++;
            //printf("\n %c", identifier[index]);

            if(identifier[index] == '\0') {//non si ferma quando incontra
                result++;
                isCorrect = false;
            } else if(identifier[index] != c) {
                isCorrect = false;
            }
        } else {
            switch (c)
            {
            case ' ':
                isNewWord = true;
                break;

            case '\n':
                //short comment end
                if(isShortComment) isShortComment = false;
                if(isMacro) isMacro = false;
                break;
            
            case '"':
                if(!isString)
                    isString = true;
                else
                    isString = false;
                break;

            case '#':
                isMacro = true;
                break;

            case '/':
                if(!slashFlag) 
                    slashFlag = true;
                else 
                    //short comment start
                    isShortComment = true;

                //longcomment end
                if(asteriscFlag) isLongComment = false;
                break;

            case '*':
                //longcomment start
                if(slashFlag) isLongComment = true;
                asteriscFlag = true;
                break;

            default:
                if(slashFlag) slashFlag = false;
                if(asteriscFlag) asteriscFlag = false;
                
                if(!isShortComment && !isLongComment && !isMacro && !isString && isNewWord) {
                    isNewWord = false;
                    index = 0;
                    
                    if(identifier[index] == c) isCorrect = true;
                }

                break;
            }
        }
    }
    
    printf("%d\n", result); // print the result
    return 0;
}

/*
0 = 3
1 = 2
*/