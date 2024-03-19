#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


unordered_map<string, char> init(){
    string sounds[] = {
        "clank",
        "bong",
        "click",
        "tap",
        "poing",
        "clonk",
        "clack",
        "ping",
        "tip",
        "cloing",
        "tic",
        "cling",
        "bing",
        "pong",
        "clang",
        "pang",
        "clong",
        "tac",
        "boing",
        "boink",
        "cloink",
        "rattle",
        "clock",
        "toc",
        "clink",
        "tuc",
    };
    unordered_map<string, char> dict;
    int len = 26;
    for(int i=0;i<len;i++){
        dict[sounds[i]] = 'a'+i;
    }
    dict["whack"] = ' ';
    dict["pop"] = '?';
    dict["bump"] = '?';
    dict["dink"] = '?';
    dict["thumb"] = '?';
    return dict;
}

void print_map(unordered_map<string,char> map){
    for(auto const &pair:map){
        cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main(){
    int N;
    cin >> N;
    unordered_map<string, char> letters = init();
    string output = "";
    bool shift = false;
    bool caps = false;
    //print_map(letters);
    for(int i=0;i<N;i++){
        string sound;
        cin >> sound;
        char val = letters[sound];
        if(val=='?'){
            if(sound == "pop"){
                if(!output.empty()) output.pop_back();
            }else if(sound == "bump"){
                caps = !caps;
            }else if(sound == "dink"){
                shift = true;
            }else if(sound == "thumb") shift = false;
        }else{
            if(shift != caps) output.push_back(toupper(val));
            else output.push_back(val);
        }
    }
    cout << output<< endl;
    return 0;
}