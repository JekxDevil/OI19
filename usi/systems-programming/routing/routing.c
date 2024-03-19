#include <stdio.h>
#include "routing.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct point
{
    char *name;
    double x;
    double y;
    struct point *next;
};

static struct point *head = 0;

void routing_clear()
{
    while (head)
    {
        struct point *next = head->next;
        free(head->name);
        free(head);
        head = next;
    }
}

int routing_set_point(const char *name, double x, double y)
{
    // look for the string
    for (struct point *p = head; p != 0; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            p->x = x;
            p->y = y;
            return 1;
        }
    }

    // create the string
    struct point *newp = malloc(sizeof(struct point));
    if (newp == 0)
        return 0;
    newp->name = malloc(strlen(name));
    if (newp->name == 0)
        return 0;
    strcpy(newp->name, name);
    newp->x = x;
    newp->y = y;
    newp->next = head;
    head = newp;
    return 1;
}

double get_distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

struct point *get_point(const char *name)
{
    for (struct point *p = head; p != 0; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            return p;
        }
    }
    return 0;
}

double routing_total_distance(const char *path)
{
    double total = 0;
    char *pathcopy = malloc(strlen(path));
    if (!pathcopy)
        return -1;
    strcpy(pathcopy, path);
    char *name = strtok(pathcopy, ",");
    if (name == 0)
        return -1;
    struct point *prev = get_point(name);
    if (prev == 0)
        return -1;
    name = strtok(0, ",");
    while (name)
    {
        struct point *next = get_point(name);
        if (next == 0)
            return -1;
        total += get_distance(prev->x, prev->y, next->x, next->y);
        prev = next;
        name = strtok(0, ",");
    }
    free(pathcopy);
    return total;
}