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
    //freopen("input1.txt", "r", stdin);
    //freopen("output1.txt", "w", stdout);
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
                    //short comment end
                    if(isShortComment) isShortComment = false;
                    if(isMacro) isMacro = false;
                    isNewWord = true;
                    break;
                
                case '"':
                    if(!isString) {
                        isString = true;
                    } else {
                        isString = false;
                    }
                    break;

                case '#':
                    if(!isString) isMacro = true;
                    break;

                case '/':

                    if(!slashFlag) {
                        slashFlag = true;
                    } else if(!isString && !isLongComment){//already flag true
                        isShortComment = true;
                    } else if(!isString && isLongComment && asteriscFlag) {
                        isLongComment = false;
                    }
                    
                    isNewWord = true;
                    break;

                case '*':
                    //longcomment start
                    if(slashFlag && !isString) isLongComment = true;
                    asteriscFlag = true;
                    isNewWord = true;
                    break;

                default:

                    slashFlag = false;
                    asteriscFlag = false;
                    
                    if(!isShortComment && !isLongComment && !isMacro && !isString && isNewWord) {
                        
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