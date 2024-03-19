#include <cstdio>
#include <map>
#include <unordered_set>
#include <set>
#include <string>
#include <vector>

#include "s_table.h"

struct s_table {
    std::unordered_set<std::string> records;

    int add(const std::string& r) {
        return records.insert(r).second;
    }

    int remove(const std::string& r) {
        return (int)records.erase(r);
    }

};

s_table* s_table_new() { return new s_table(); }

void s_table_delete(s_table* t) { delete t; }

// clean all stuff but keep object
void s_table_clear(s_table* t) { t->records.clear(); }

int s_table_add_record(s_table* t, const char* begin, const char* end) {
    std::string record(begin, end);
    return t->add(record);
}

int s_table_remove_record(s_table* t, const char* begin, const char* end) {
    std::string record(begin, end);
    return t->remove(record);
}

size_t s_table_remove_records(s_table* t, feature_extractor selector_callback) {
    int removed = 0;
    std::vector<std::string> to_remove;
    for (auto& r : t->records) {
        const char* begin = r.c_str();
        const char* end = begin + r.size();
        int result = selector_callback(begin, end);
        if (result) {
            to_remove.push_back(r);
            removed++;
        }
    }

    for (auto& s : to_remove)
        t->records.erase(s);

    return removed;
}

size_t s_table_max_feature(s_table* t, feature_extractor feature_callback,
                           char* record, size_t record_max_len) {

    if (t->records.empty()) return 0;

    std::pair<std::string, int> max_feature{"", 0};
    for (auto& r : t->records) {
        const char* b = r.c_str();
        const char* e = b + r.size();
        int score;
        if (((score = feature_callback(b, e)) && score > max_feature.second) || max_feature.first.empty())
            max_feature = {r, score};
    }

    if (max_feature.first.empty()) return 0;

    // copy to record
    size_t i;
    for (i = 0; i < record_max_len && i < max_feature.first.size(); i++)
        *(record + i) = max_feature.first[i];

    *(record + i) = '\0';
    return i;
}

void s_table_print_sorted(s_table* t, FILE* f, feature_extractor feature_callback) {
    std::map<int, std::set<std::string>> ordered;
    for (auto& r : t->records) {
        const char* b = r.c_str();
        const char* e = b + r.size();
        int result = feature_callback(b, e);
        if (result)
            ordered[result].insert(r);
    }

    for (auto& r : ordered)
        for (auto& s : r.second)
            fprintf(f, "%s\n", s.c_str());
}
