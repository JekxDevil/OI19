#include "processes.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proc {
    int pid;
    int ppid;
    char user[8 + 1];
    int priority;
    float cpu_usage;
    long int rss;
    long int size;
    long int vsize;
    char command[15 + 1];
    struct proc *next;
};

struct processes {
    struct proc *start;
    struct proc *end;
};

struct query_result {
    // change
    struct proc *start;
    struct proc *end;
};

struct processes *new_processes() {
    struct processes *p = malloc(sizeof(struct processes));
    if (p == NULL) return NULL;
    p->start = NULL;
    p->end = NULL;
    return p;
}

void delete (struct processes *p) {
    clear(p);  // remove elements inside (processes)
    free(p);   // remove collection of processes
}

int add_from_file(struct processes *p, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return *((int *)NULL);

    // assuming well formatted file
    struct proc new;
    while (fscanf(f, "%d %d %8s %d %f %ld %ld %ld %15s",
                  &(new.pid), &(new.ppid), new.user, &(new.priority), &(new.cpu_usage),
                  &(new.rss), &(new.size), &(new.vsize), new.command) == 9) {
        new.next = NULL;
        struct proc *this = malloc(sizeof(struct proc));
        if (this == NULL) {
            fclose(f);
            return *((int *)NULL);
        }
        memcpy(this, &new, sizeof(struct proc));
        this->next = NULL;
        if (p->start == NULL) {
            // if processes is empty, set as first and as last
            p->start = this;
            p->end = this;
        } else {
            // otherwise, add as next of last element and update last in list
            p->end->next = this;
            p->end = this;
        }
    }
    fclose(f);
    return 1;
}

void clear(struct processes *p) {
    struct proc *cur = p->start;
    while (cur) {
        struct proc *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    p->start = NULL;
    p->end = NULL;
}

int match(struct proc *p, const struct query *q) {
    if (q->priority != 0 && ((q->priority < 0 && -q->priority > p->priority) || (q->priority > 0 && q->priority != p->priority))) return 0;
    if (q->rss != 0 && ((q->rss < 0 && -q->rss > p->rss) || (q->rss > 0 && q->rss != p->rss))) return 0;
    if (q->size != 0 && ((q->size < 0 && -q->size > p->size) || (q->size > 0 && q->size != p->size))) return 0;
    if (q->vsize != 0 && ((q->vsize < 0 && -q->vsize > p->vsize) || (q->vsize > 0 && q->vsize != p->vsize))) return 0;
    if (q->cpu_usage != 0 && ((q->cpu_usage < 0 && -q->cpu_usage > p->cpu_usage) || (q->cpu_usage > 0 && q->cpu_usage != p->cpu_usage))) return 0;
    return 1;
}

struct query_result *search(struct processes *p, const struct query *q) {
    if (p == NULL || q == NULL) return NULL;
    struct query_result *res = malloc(sizeof(struct query_result));
    if (res == NULL) return NULL;
    res->start = NULL;
    res->end = NULL;
    struct proc *cur = p->start;
    if (cur == NULL) return NULL;
    while (cur) {
        if (match(cur, q)) {
            struct proc *new = malloc(sizeof(struct proc));
            if (new == NULL) return NULL;
            memcpy(new, cur, sizeof(struct proc));
            new->next = NULL;
            if (res->start == NULL) {
                res->start = new;
                res->end = new;
            } else {
                res->end->next = new;
                res->end = new;
            }
        }
        cur = cur->next;
    }
    if (res->start == NULL) {
        free(res);
        return NULL;
    }
    return res;
}

int get_pid(struct query_result *r) {
    return r->start->pid;
}

int get_ppid(struct query_result *r) {
    return r->start->ppid;
}

const char *get_user(struct query_result *r) {
    return r->start->user;
}

int get_priority(struct query_result *r) {
    return r->start->priority;
}

float get_cpu_usage(struct query_result *r) {
    return r->start->cpu_usage;
}

long int get_rss(struct query_result *r) {
    return r->start->rss;
}

long int get_size(struct query_result *r) {
    return r->start->size;
}

long int get_vsize(struct query_result *r) {
    return r->start->vsize;
}

const char *get_command(struct query_result *r) {
    return r->start->command;
}

struct query_result *next(struct query_result *r) {
    struct proc *tmp = r->start;
    r->start = r->start->next;  // implicit set to NULL
    if (r->start == NULL) {
        free(r);
        return NULL;
    }
    // check if ended list start == end + 1
    free(tmp);
    return r;
}

void terminate_query(struct query_result *r) {
    struct proc *cur = r->start;
    while (cur) {
        struct proc *tobefreed = cur;
        cur = cur->next;
        r->start = cur;
        free(tobefreed);
    }
    free(r);
}
