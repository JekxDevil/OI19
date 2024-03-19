#include <stdlib.h>
#include "simplesets.h"
//INTERESTING FOR OBJECT UNDEFINED BEHAVIOR

struct ss {
    struct ss * parent;     // first representative element of the set
    struct ss * next;       // next element
    struct ss * global_next;    // next element in the global allocation list
};

static struct ss * global = 0;  // head of the allocation list

struct ss * ss_create_singleton() {
    struct ss * singleton = malloc(sizeof(struct ss));
    if(!singleton) return 0;
    singleton->parent = singleton;
    singleton->next = 0;
    singleton->global_next = global;
    global = singleton;
    return singleton;
}

void ss_destroy_all(){
    struct ss * traversing = global;
    while (traversing) {
        struct ss * tobefreed = traversing;
        traversing = traversing->next;
        global->next = traversing;
        free(tobefreed);
    }
}

void ss_merge(struct ss * X, struct ss * Y) {
    if (X->parent == Y->parent) return;
    struct ss * traversing = X->parent;
    while (traversing->next) {
        traversing = traversing->next;
    }
    traversing->next = Y->parent;
    traversing = traversing->next;  // who is afterwards
    do {
        traversing->parent = X->parent;
        traversing = traversing->next;
    } while (traversing);

}

int ss_disjoint(struct ss * X, struct ss * Y) {
    return X->parent != Y->parent;
}
