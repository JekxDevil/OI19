#include "lists.h"

struct list * concatenate_all(int count, struct list * lists[]) {
    struct list * result = 0;
    struct list ** traversing = &result;

    for (int i = 0; i < count; i++) {
        struct list * l = lists[i];
        if (!l) continue;
        *traversing = l;
        while (l->next) {
            l = l->next;
        }
        traversing = &(l->next);
    }

    return result;
}

struct list * merge_sorted(struct list * a, struct list * b) {
    struct list * result = 0;
    struct list ** traversing = &result;

    while (a || b) {
        if (a != 0 && (b == 0 || a->value < b->value)) {
            *traversing = a;
            traversing = &(a->next);
            a = a->next;
        } else {
            *traversing = b;
            traversing = &(b->next);
            b = b->next;
        }
    }
    return result;
}
