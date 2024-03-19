#include <stdio.h>
#include <assert.h>
#include <ctype.h>

// constraints
#define MAXL 100000

// input data
char identifier[MAXL + 1];
char before = '\0';
long long result;
long long my_index;
bool isShortComment = false, isLongComment = false, isString = false, isNewWord = true, isCorrect = false;

//switch characters by their syntax meaning and manage main boolean program values
void Processing(char& ch){
    
    switch (ch) {
            case '\n':
                isShortComment = false;
                isString = false;
            case ' ':
            case '\t':
            case '!':
            case '%':
            case '^':
            case '&':
            case '(':
            case ')':
            case '-':
            case '=':
            case '+':
            case '[':
            case ']':
            case '{':
            case '}':
            case '|':
            case ';':
            case ':':
            case '<':
            case '>':
            case '~':
                isNewWord = true;
                break;

            case '/':
                if(!isString && !isShortComment){
                    if(before == '/' && !isLongComment)
                        isShortComment = true;
                    
                    if(before == '*' && isLongComment) {
                        isLongComment = false;
                        ch = '\0';//avoid case /* *// = short comment true 
                    }
                }

                isNewWord = true;
                break;

            case '*':
                if(!isString && !isShortComment) {

                    if(before == '/') {
                        isLongComment = true;
                        ch = '\0';  //avoid case /*/ 
                    }
                }

                isNewWord = true;
                break;
            
            case '"':
                if(!isShortComment && !isLongComment)
                    isString = isString ? false : true; 

                isNewWord = true;
                break;
                
            default:

                if(!isShortComment && !isLongComment && !isString && isNewWord) {
                    
                    if(identifier[0] == ch){
                        isCorrect = true;
                        my_index = 0;
                    } else
                        isCorrect = false;
                }

                isNewWord = false;
                break;
        }
}

//compare identifier if there's a first match, else pass character to the processing func
void Scanning(char& ch){

    if(isCorrect) {
        my_index++;
        
        if(identifier[my_index] != ch) {

            if(identifier[my_index] == '\0' && !isalnum(ch) && ch != '_')
                result++;

            Processing(ch);
            isCorrect = false;
        }

    } else
        Processing(ch);

    before = ch;
}

int main() {
    result = 0;
    assert(1 == scanf("%s", identifier));
    char c;
    
    //ascii reading
    while ((c = getchar()) != EOF)
        Scanning(c);

    printf("%lld\n",result);
    return 0;
}