#include <string>
#include <map>
#include <set>

#include "media_stats.h"

struct segment {
    double start;
    double finish;
    segment(double s, double f) : start(s), finish(f) {};
};

bool operator < (const segment & a, const segment & b) {
    return a.start < b.start || (a.start == b.start && a.finish < b.finish);
}

struct media {
    double duration;
    // views: user -> set of (start,finish) segments 
    std::map <std::string, std::set <segment> > views;
    media(double d) : duration(d) {};
};

// M: title -> media
static std::map < std::string, media > M;

void clear_media() {
    M.clear();
}

void clear_views() {
    for (auto & m : M)
	m.second.views.clear();
}

int add_media(const char * title, double duration) {
    if (duration <= 0)
	return 0;
    return M.insert({title, media(duration)}).second;
}

int add_view(const char * title, const char * user, double start, double finish) {
    auto m = M.find(title);
    if (m != M.end() && 0 <= start && start < finish && finish <= m->second.duration) {
	m->second.views[user].insert(segment(start, finish));
	return 1;
    }
    return 0;
}

static double time_viewed(const std::set<segment> & views) {
    double result = 0.0;
    double t = -1.0; 		// latest finish time seen so far
    for (const auto & v : views) {
	if (v.start > t) {
	    result += v.finish - v.start;
	    t = v.finish;
	} else if (v.finish > t) {
	    result += v.finish - t;
	    t = v.finish;
	}
    }
    return result;
}

int complete_views(const char * title) {
    auto m = M.find(title);
    if (m == M.end())
	return -1;
    unsigned int total = 0;
    for (const auto & v : m->second.views)
	if (time_viewed(v.second) >= m->second.duration)
	    total += 1;
    return total;
}

int unique_viewers(const char * title) {
    auto m = M.find(title);
    if (m == M.end())
	return -1;
    return m->second.views.size();
}

double total_time_viewed(const char * title, const char * user) {
    auto m = M.find(title);
    if (m == M.end())
	return -1.0;
    auto u = m->second.views.find(user);
    if (u == m->second.views.end())
	return 0.0;
    return time_viewed(u->second);
}
