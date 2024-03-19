#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <vector>
#include <algorithm>

unsigned int f_low = 10;	// low=<number>
unsigned int f_high = 90;	// high=<number>

bool fancy_output = false;	// -f
bool reverse_order = false;	// -r

bool read_word(std::istream & input, std::string & w) {
    w.clear();
    char c;
    while (input.get(c)) {
	if (isalpha(c))
	    w += c;
	else {
	    if (w.size() == 0)
		continue;
	    return true;
	}
    }
    return (w.size() > 0);
}

struct word_count {
    std::string word;
    unsigned int count;

    word_count(std::string w, unsigned int c)
	: word(w), count(c) {};

    bool operator < (const word_count & other) const {
	if (reverse_order) 
	    return (count > other.count) || (count == other.count && word > other.word);
	else 
	    return (count < other.count) || (count == other.count && word < other.word);
    }
};

void process_input(const char * filename, std::istream & input) {
    std::string w;
    std::map<std::string, unsigned int> C;
    unsigned int total = 0;
    while (read_word(input, w)) {
	C[w] += 1;
	total += 1;
    }
    std::vector<word_count> WC;
    for (auto i = C.begin(); i != C.end(); ++i) {
	unsigned int f = i->second * 100 / total;
	if (f >= f_low && f <= f_high)
	    WC.push_back(word_count(i->first, i->second));
    }

    std::sort(WC.begin(), WC.end());

    std::cout << filename;

    if (fancy_output) {
	for (auto i = WC.begin(); i != WC.end(); ++i) 
	    std::cout << ' ' << i->count << "/" << total << ':' << i-> word;
    } else {
	for (auto i = WC.begin(); i != WC.end(); ++i) 
	    std::cout << ' ' << i-> word;
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    int i;
    for (i = 1; i < argc; ++i) {
	if (sscanf(argv[i], "low=%u", &f_low) == 1)
	    continue;
	if (sscanf(argv[i], "high=%u", &f_high) == 1)
	    continue;
	if (strcmp(argv[i], "-f") == 0) {
	    fancy_output = true;
	    continue;
	}
	if (strcmp(argv[i], "-r") == 0) {
	    reverse_order = true;
	    continue;
	}
	if (strcmp(argv[i], "--") == 0) {
	    ++i;
	    break;
	}
	break;
    }
    if (i < argc) {
	// reading file names from the command line
	do {
	    std::ifstream input(argv[i]);
	    if (input) {
		process_input(argv[i], input);
		input.close();
	    } else {
		std::cerr << "could not open file " << argv[i] << std::endl;
	    }
	} while (++i < argc);
    } else {
	// reading from standard input
	process_input("(stdin)", std::cin);
    }
}

