#include <stdio.h>
#include <assert.h>

// constraints
#define MAXL 100000

// input data
char identifier[MAXL + 1];

int main() {
    long long result = 0, index = 0;
    bool isShortComment = false, isLongComment = false, slashFlag = false, asteriscFlag = false, isString = false, isNewWord = false, isCorrect = false;

    //  uncomment the following lines if you want to read/write from files
    freopen("input0.txt", "r", stdin);
    freopen("output0.txt", "w", stdout);
    assert(1 == scanf("%s", identifier));
    char c;
    
    //ascii reading
    while ((c = getchar()) != EOF) {

        if(isCorrect) {
            index++;

            if(identifier[index] == '\0') {
                result++;
                isCorrect = false;
            } else if(identifier[index] != c) {
                isCorrect = false;
            }
        } else {

            switch (c) {
                case ' ':
                case '+':
                case '-':
                case '%':
                case '!':
                case '&':
                case '|':
                case '<':
                case '>':
                case '^':
                case '~':
                case '(':
                case ')':
                case '{':
                case '}':
                case '[':
                case ']':
                case '.':
                case ';':
                case '=':
                case ':':
                    isNewWord = true;
                    break;

                case '\n':
                    //short comment ends (anyway)
                    isShortComment = false;
                    isNewWord = true;
                    break;
                
                case '"':
                	if(!isShortComment && !isLongComment){
                		isString = !isString ? true : false;
                	}

                    isNewWord = true;
                    break;

                case '/':

                    if(slashFlag && !isString && !isLongComment){//already flag true
                        isShortComment = true;
                    } else if(!isShortComment && !isString && isLongComment && asteriscFlag) {
                        isLongComment = false;
                    } else
                        slashFlag = true;
                    
                    isNewWord = true;
                    break;

                case '*':
                    //longcomment start
                    if(slashFlag && !isString && !isShortComment) 
                        isLongComment = true;
                    else
                        asteriscFlag = true;
                    
                    isNewWord = true;
                    break;

                default:

                    slashFlag = false;
                    asteriscFlag = false;
                    
                    if(!isShortComment && !isLongComment && !isString && isNewWord) {
                        
                        if(identifier[0] == c) {
                            index = 0;
                            isCorrect = true;
                        }
                    }

                    isNewWord = false;
                    break;
            }
        }
    }
    
    printf("%lld\n", result); // print the result
    return 0;
}
