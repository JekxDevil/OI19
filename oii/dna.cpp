#include <iostream>
#include <string>

using namespace std ;

int main() 
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int _iTotalTestcases, _iTotalPieces;
    string _sDna;

    cin >> _iTotalTestcases;
    for(int _iTestcase = 1; _iTestcase <= _iTotalTestcases; _iTestcase++)
    {
        cin >> _iTotalPieces;
        cin >> _sDna;

        int pos = 0, last = 0, j;

        //for each piece of dna get the minimun lenght assemblable
        for(int i = 1; i < _iTotalPieces; i++)
        {
            string s;
            cin >> s;

            //flowing correctly
            bool st = false;
            for(j = last + 1; j < _sDna.size() && !st; j++)
            {
                st = true;

                //if pieces aren't assemblable
                for(pos = 0; pos < s.size() && j + pos < _sDna.size() && st; pos++)
                    if(s[pos] != _sDna[j + pos])
                        st = false;
            }

            //if pieces is a substring of the current dna string, nothing gets triggered

            //if pieces are completly assemblable set last index to the end of the string
            if(st && pos == s.size())
                last = j - 1;
            
            //if substring aren't completly assemblable then add the substring and update last index
            if(st && pos < s.size() && j - 1 + pos == _sDna.size()) 
            {
                _sDna = _sDna + s.substr(pos);
                last = j - 1;
            }

            //if non assemblable then add the substring and update the last index
            if(!st)
            {
                last = _sDna.size();
                _sDna = _sDna + s;
            }
        }

        cout << "Case #" << _iTestcase << " : " << _sDna.size() << " \n";
    }
 }