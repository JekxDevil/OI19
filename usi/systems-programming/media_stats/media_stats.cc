/*
 * title is unique.
 */
#include <string>
#include <unordered_map>
#include <set>

#include "media_stats.h"

using std::string;
using std::unordered_map;
using std::set;

struct Media {

    struct Segment {
        double start;
        double end;
        Segment(double &s, double &e): start(s), end(e) {}

        bool operator<(const Segment &other) const {
            const bool& start_equal = start < other.start;
            return start_equal || (start_equal && end < other.end);
        }
    };

    double duration_s{};
    unordered_map<string, set<Segment>> viewers; // ordered map key: user name, value: inc segments

    Media() = default;
    explicit Media(double d): duration_s(d) {};

    static bool out_of_bounds(const double &s, const double &e, const double &limit) {
        if (s < 0 || e < 0) return true;
        if (limit < e) return true;
        return false;
    }
};

unordered_map<string, Media> medias;

bool exist_title(const string &title) {
   return medias.find(title) != medias.end();
}

bool exist_user(const string &title, const string &user) {
    auto& media = medias[title];
    return media.viewers.find(user) != media.viewers.end();
}

/**
 * Add media file in db.
 * title must be new.
 * duration greater than 0
 * @param title c string
 * @param duration int in seconds
 * @return 1 on success, else 0. otherwise db unchanged bad_alloc exception when memory allocation fails
 */
int add_media(const char *title, double duration) {
    // fire conditions:
    // check duration greater than 0.
    if (duration <= 0) return 0;

    // add media
    return medias.insert({title, Media(duration)}).second;
}

/**
 * Records a viewing of a media file
 * title must exist.
 * start and finish must be valid and consistent with media file duration.
 * start <= finish.
 * @param title c string
 * @param user c string
 * @param start second where you started
 * @param finish seconds where you finished the view
 * @return 1 on success, else 0. std::bad_alloc when memory allocation fails.
 */
int add_view(const char *title, const char *user, double start, double finish) {
    // fire conditions:
    // check duration segment > 0
    // check if title exist
    // check if segment ends before media limit
    if (start >= finish) return 0;
    if (!exist_title(title)) return 0;
    if (Media::out_of_bounds(start, finish, medias[title].duration_s)) return 0;

    // add segment in title for the given user
    return (medias[title].viewers[user].insert(Media::Segment(start, finish))).second;
}

/**
 * Removes all the media medias and the viewings.
 */
void clear_media() {
    medias.clear();
}

/**
 * Clear all media views but keep media themselves.
 */
void clear_views() {
    for (auto &[t, m] : medias)
        m.viewers.clear();
}

/**
 * Give number of unique users who viewed the media.
 * Any view of non-zero duration counts.
 * 2 >= views from one user count as 1.
 * @param title c string
 * @return -1 if not-existent title, # unique users on success.
 */
int unique_viewers(const char* title) {
    if (!exist_title(title)) return -1;
    return int(medias[title].viewers.size());
}

double time_viewed(const set<Media::Segment> &segments) {
    double tot = 0.0;
    double prev_end = -1.0;

    for (auto &[start, end] : segments) {
        if (prev_end <= start) {
            // don't intersect
            tot += end - start;
        } else if (prev_end < end){
            // intersect at right
            tot += end - prev_end;
        }
        prev_end = end;
    }

    return tot;
}

/**
 * Give total time of viewed time by a single user in seconds.
 * overlapping segment views count once.
 * @param title c string
 * @param user c string
 * @return -1.0 if not existent title, 0.0 if title exist but user hasn't seen it.
 */
double total_time_viewed(const char *title, const char *user) {
    if (!exist_title(title)) return -1.0;
    if (!exist_user(title, user)) return 0.0;
    return time_viewed(medias[title].viewers[user]);
}

/**
 * Give # users viewed media completely at least once.
 * @param title c string
 * @return -1 if title doesn't exist.
 */
int complete_views(const char *title) {
    // fire conditions:
    // check if title media exists
    if (!exist_title(title)) return -1;

    int result = 0;
    for (auto &[n, segments] : medias[title].viewers)
        if (medias[title].duration_s <= time_viewed(segments))
            result++;

    return result;
}
