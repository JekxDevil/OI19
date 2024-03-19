/*
 * extracts important words from text files.
 * A word is a sequence of one or more consecutive alphabetic characters as defined by the isalpha function
 * of the standard C library.
 * The program must read one or more files, or the standard input, and for each file
 * it must print on the standard output the words that occur within a range of frequencies l ≤ fw ≤ h.
 * The frequency fw of a word w in a file is the number of times that w occurs in the file divided by the total
 * number of words in that file.
 * Frequencies are expressed in percentage values as integers between 0 and 100.
 * The default values are l = 10 and h = 90, meaning that the program must output words
 * with frequencies between 10% and 90%.
 *
 * Output
 * print on the standard output. There are two required output formats:
 * simple and fancy.
 * The simple output (default) is a list of words for each input file.
 * The fancy output is a list of words with their frequencies.
 * More specifically, with simple output, for each input file name x, the program must output one line as follows:
 * x w1 w2 ...
 * The output line starts with the file name x, or the empty string for the standard input, and for each output word wi
 * continues with a space followed by the word wi.
 * With “fancy” output, for each input file name x, the program must output one line:
 * x c1:w1 c2:w2 ...
 * The output line starts with the file name x, or the empty string for the standard input, and for each output word wi
 * continues with a space followed by the number ci of occurrences of word wi, followed by a colon (‘:’),
 * followed by the word wi.
 * For each input file, the output words must be sorted in descending order of frequency.
 * If two words have the same frequency, the order must be lexicographical as defined by the ASCII code for each
 * alphabetic character, so all upper-case letter lexicographically precede all lower-case letters.
 *
 * Command-line parameters
 * The names of the input files can be specified with command-line parameters. The default is the standard input.
 * The program must also accept the following command-line options, in any order, before the file names.
 * • low=l specifies that the minimum frequency to be considered is l.
 * The program must output only words with relative frequency fw ≥ l.
 * l is given as an integer and represents a percentage value.
 * • high=h specifies that the maximum frequency to be considered is h.
 * The program must output only words with relative frequency fw ≤ h.
 * h is given as an integer and represents a percentage value.
 * • -f selects the fancy output, so each word must be preceded by its count.
 * • -r inverts the ordering of words by frequency: lower-frequency first.
 * Same-frequency words must still be ordered lexicographically.
 * • -- interprets every subsequent command-line option as a filename.
 * This way, the program may also process input file names such as “-f” or “high=23”.
*/
#define DEBUG 0

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::string;

bool print_fancy = false;
bool increasing = false;
bool from_stdin = true;
std::pair<int, int> range{10, 90};

bool is_word(const string& s) {
    for (auto& c : s)
        if (!std::isalpha(c))
            return false;
    return true;
}

int main(int argc, char* argv[]) {
    // read params
    std::vector<std::pair<string, int>> files;

    for (int i = 1; i < argc; i++) {
        string param(argv[i]);
        if (!from_stdin) {
            files.emplace_back(param, 0);
        } else {
            if (param == "--") {
                from_stdin = false;
            } else if (param == "-f") {
                print_fancy = true;
            } else if (param == "-r") {
                increasing = true;
            } else if (param.substr(0, 4) == "low=") {
                param = param.substr(4, std::string::npos);
                int low = std::stoi(param);
                if (low < 0) low = 0;
                range.first = low;
            } else if (param.substr(0, 5) == "high=") {
                param = param.substr(5, std::string::npos);
                int high = std::stoi(param);
                if (high > 100) high = 100;
                range.second = high;
            } else {
                // is a file apparently
#if DEBUG
                cout << "newfile: " << param << endl;
#endif
                from_stdin = false;
                files.emplace_back(param, 0);
            }
        }
    }
#if DEBUG
    cout << "1------------------------" << endl;
#endif

    if (from_stdin) files.emplace_back("", 0);
#if DEBUG
    cout << "2------------------------" << endl;
#endif
    for (auto& filename_words : files) {
        if (!from_stdin)
            cout << filename_words.first;

        std::ifstream to_close;
        std::istream* in;
        if (from_stdin) in = &std::cin;
        else {
            to_close.open(filename_words.first);
            in = &to_close;
        }
#if DEBUG
        cout << "3------------------------" << endl;
#endif

        std::unordered_map<std::string, int> keywords;
        string line;
        while (std::getline(*in, line)) {
            std::istringstream line_stream(line);
            string raw_word;
            while (line_stream >> raw_word) {
                string word;
                for (auto& c : raw_word) {
                    if (std::isalpha(c)) {
                        word += c;
                    } else {
                        if (!word.empty()) {
                            filename_words.second++;
                            if (keywords.find(word) != keywords.end())
                                keywords[word]++;
                            else
                                keywords.insert({word, 1});
                        }
                        word.clear();
                    }
                }

                if (!word.empty()) {
                    filename_words.second++;
                    if (keywords.find(word) != keywords.end())
                        keywords[word]++;
                    else
                        keywords.insert({word, 1});
                }
                word.clear();
            }

            /*
             * string word;
            while (line_stream >> word) {
                if (!is_word(word)) continue;
                filename_words.second++;

                if (keywords.find(word) != keywords.end())
                    keywords[word]++;
                else
                    keywords.insert({word, 1});
            }
             */
        }
#if DEBUG
        cout << "words: " << filename_words.second << endl;
        for (auto& p: keywords) {
            cout << p.first << " " << p.second << endl;
        }
        cout << endl;
        cout << "4------------------------" << endl;
#endif

        std::map<int, std::set<string>> ordered;
        for (auto& key_freq : keywords) {
            ordered[key_freq.second].insert(key_freq.first);
        }
#if DEBUG
        cout << "5------------------------" << endl;
#endif


        if (increasing) {
            for (auto & freq_keys : ordered) {
                for (auto &k: freq_keys.second) {
                    int freq = freq_keys.first * 100 / filename_words.second;
#if DEBUG
                    cout << freq_keys.first << " / " << filename_words.second  << " = " << freq << endl;
                    cout << range.first << " <= " << freq << " <= " << range.second << endl;
#endif
                    if (freq < range.first || freq > range.second) continue;
                    cout << " ";
                    if (print_fancy) cout << freq_keys.first << ":";
                    cout << k;
                }
            }
#if DEBUG
            cout << "6------------------------" << endl;
#endif
        } else {

            for (auto freq_keys = ordered.rbegin(); freq_keys != ordered.rend(); freq_keys++) {
                for (auto &k: freq_keys->second) {
                    int freq = freq_keys->first * 100 / filename_words.second;
#if DEBUG
                    cout << freq_keys->first << " / " << filename_words.second  << " = " << freq << endl;
                    cout << range.first << " <= " << freq << " <= " << range.second << endl;
#endif
                    if (freq < range.first || freq > range.second) continue;
                    cout << " ";
                    if (print_fancy)
                        cout << freq_keys->first << /*"/" << filename_words.second << */ ":";
                    cout << k;
                }
            }
#if DEBUG
            cout << "6------------------------" << endl;
#endif
        }

        if (!from_stdin) to_close.close();
        cout << endl;

#if DEBUG
        cout << "7------------------------" << endl;
#endif
    }
}
