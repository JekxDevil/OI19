#include <iostream>
#include <map>
#include <set>

using std::map;
using std::set;
using std::getchar;
using std::isalpha;
using std::to_string;
using std::cout;
using std::endl;
using std::toupper;

map<int, map<int, unsigned>> char_freq;

int main() {
    int prev = -1;
    int current_char;

    if ((prev = toupper(getchar())) == EOF) return 0;
    while ((current_char = toupper(getchar())) != EOF) {
        if (isalpha(prev) && isalpha(current_char))
            char_freq[prev][current_char]++;

        prev = current_char;
    }

    // order now
    map<int, map<unsigned, set<int>, std::greater<>>> ordered_freq;
    for (auto& c_c1_freq : char_freq)
        for (auto& c1_freq : c_c1_freq.second)
            ordered_freq[c_c1_freq.first][c1_freq.second].insert(c1_freq.first);

    for (auto& c_freq_c1s : ordered_freq) {
        auto& map_freq_set_char = c_freq_c1s.second;
        const auto& c = (unsigned char)c_freq_c1s.first;
        const auto& c1 = (unsigned char)*(*map_freq_set_char.begin()).second.begin();
        cout << c << c1 << endl;
    }
}