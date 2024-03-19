#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "words.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::map;
using std::set;
using std::pair;
using std::cout;
using std::endl;

struct lines {
    int id = 0;
    vector<pair<int, string>> given_lines;
    unordered_map<int, int> id_to_pos;
};

lines *lines_create() {
    return new lines();
}

void lines_destroy(lines *l) {
    delete l;
}

int add_line(lines *l, const char *line) {
    // not empty
    if (string(line).empty()) return -1;
    l->given_lines.emplace_back(l->id, line);
    if (!l->id_to_pos.insert({l->id, l->given_lines.size()-1}).second)
        return -1;
    return l->id++;
}

int remove_line(lines *l, int id) {
    auto id_pos = l->id_to_pos.find(id);
    if (id_pos == l->id_to_pos.end()) return false;
    int pos = id_pos->second;
    l->id_to_pos.erase(id);
    l->given_lines[pos].second = "";
    return true;
}

int match(lines *l, const char *output[], int max_output, const char *words) {
    int idx_out = 0;
    map<int, string> matched;
    unordered_map<char, string> words_search;

    if (string(words).empty()) return 0;

    string words_string(words);
    std::istringstream w_stream(words_string);
    string word;
    cout << endl << "sssssss" << endl;
    while (w_stream >> word) {
        // cout << word[0] << " " << word << endl;
        words_search.insert({word[0], word});
    }

    for (auto &[id, pos] : l->id_to_pos) {

        string current_line = l->given_lines[pos].second;

        int tot_matches = 0;
        std::istringstream current_line_stream(current_line);
        string w;
        while (current_line_stream >> w) {
            // cout << "1" << endl;
            for (auto &[start, pattern] : words_search) {
                // cout << "2" << endl;
                for (int i = 0; i < int(w.size()); i++) {
                    // cout << "3" << endl;
                    if (words_search.find(w[i]) != words_search.end()) {
                        cout << "4: " << w.substr(i, pattern.size()) << " " << pattern << endl;
                        if (w.substr(i, pattern.size()) == pattern) {
                            cout << "match!" << endl;
                            tot_matches++;
                        }
                    }
                }
            }
        }

        if (tot_matches >= int(words_search.size())) {
            // stuff if match
            matched.insert({pos, current_line});

            if (max_output < int(matched.size())) {
                break;
            }
        }
    }

    for (auto& [idx, line] : matched) {
        cout << line << endl;
        output[idx_out] = line.c_str();
        idx_out++;
    }

    return int(matched.size());
}
