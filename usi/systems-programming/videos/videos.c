//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "videos.h"
#define MAX_TITLE 100

struct video {
    //KISS video contains itself and the next
    int id;
    char title[MAX_TITLE];
    int minutes;
    int viewed_minutes;
    int viewed_full;
    struct video * next;
};

struct platform {
    struct video * listvideos;
    int count;
};

struct platform * create() {
    struct platform * this = malloc(sizeof(struct platform));
    if (this == 0) return this;
    this->listvideos = 0;
    this->count = 0;
    return this;
}

void destroy(struct platform * p) {
    //... free fields before
    clear(p);
    free(p);
}

void clear(struct platform * p) {
    //... free fields of p
    struct video * traversing = p->listvideos;
    while (traversing != 0) {
        struct video * tobefreed = traversing;
        traversing = traversing->next;
        p->listvideos = traversing; //consistency
        free(tobefreed);
    }
    p->count = 0;
}

int add_video(struct platform * p, const char * title, int minutes) {
    struct video * newvideo = malloc(sizeof(struct video));
    if (newvideo == 0) return -1;
    newvideo->id = p->count;
    p->count += 1;
    strncpy(newvideo->title, title, MAX_TITLE); // IMPORTANT FOR ASSIGNING STRINGS
    newvideo->title[99] = 0;
    newvideo->minutes = minutes;
    newvideo->viewed_minutes = 0;
    newvideo->viewed_full = 0;
    newvideo->next = p->listvideos;
    p->listvideos = newvideo;
    return newvideo->id;
}

int add_view(struct platform * p, int video_id, int minutes) {
    int found = 0;
    struct video * traversing = p->listvideos;

    while (traversing != 0 && !found) {
        if (traversing->id == video_id) {
            traversing->viewed_minutes = traversing->viewed_minutes + minutes;
            if (traversing->viewed_minutes >= traversing->minutes) {
                traversing->viewed_full += 1;
            }
            found = 1;
        } else {
            traversing = traversing->next;
        }
    }
    return found;
}

int total_view_minutes(struct platform * p) {
    int total = 0;
    struct video * traversing = p->listvideos;
    while (traversing != 0) {
        total += traversing->viewed_minutes;
        traversing = traversing->next;
    }
    return total;
}

int total_full_views(struct platform * p) {
    int total = 0;
    struct video * traversing = p->listvideos;
    while (traversing) {
        total += traversing->viewed_full;
        traversing = traversing->next;
    }
    return total;
}

int video_by_title(struct platform * p, const char * title) {
    int id = -1;
    struct video * traversing = p->listvideos;

    while (traversing && id == -1) {
        if (strcmp(traversing->title, title) == 0) {
            id = traversing->id;
        } else {
            traversing = traversing->next;
        }
    }
    return id;
}
