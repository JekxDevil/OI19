#include <iostream>
#include "snake.h"

#define DEBUG 0

using std::cout;
using std::endl;

struct snake {
    unsigned rows;      // alias max y
    unsigned columns;   // alias max x
    char* map;
    char** snake_body;  // queue of chars pointing to map cells

    std::pair<unsigned, unsigned> head = {0, 0};    // (x, y)
    unsigned queue_head = 0;        // index of queue
    unsigned direction = 0;         // default invalid
    unsigned status = SNAKE_NEW;    // immediately set status as new
    unsigned length = 0;            // current snake body length
    unsigned max_length;

    snake(int c, int r, int l)
    : rows(r), columns(c), max_length(l) {
        map = new char[r * c + 1];
        map[r * c] = 0;
        snake_body = new char*[l];
    }

    ~snake() {
        delete [] map;
        delete [] snake_body;
    };
};

/**
 * Construct a new game.
 * @param c columns
 * @param r rows
 * @param l length of the snake
 * @return snake objects pointer or nullptr
 */
snake* snake_new(int c, int r, int l) {
    if (c <= 0 || r <= 0 || l <= 0) return nullptr;
    return new snake(c, r, l);
}

void snake_destroy (snake* s) { delete s; }

int snake_fail(snake* const s) {
#if DEBUG
    cout << "3----------------------------" << endl;
#endif
    return (int)(s->status = SNAKE_FAIL);
}

void print_map(const snake* const s) {
    for (unsigned r = 0; r < s->rows; r++, cout << "|" << endl)
        for (unsigned c = 0; c < s->columns; c++)
            cout << s->map[r * s->columns + c];
}

/**
 * Gives pointer to the cell of the snake head.
 * @param s snake object pointer
 * @return pointer to char of head position
 */
char* head_ptr(snake* s) {
    return s->map + s->columns * s->head.second + s->head.first;
}

/**
 * Initialize a snake object to start a game.
 * @param s snake object pointer
 * @param c column position of snake head
 * @param r row position of snake head
 * @param d direction of snake
 * @return either SNAKE_FAIL or SNAKE_OKAY
 */
int snake_start(snake* s, int c, int r, int d) {
    if (c < 0 || r < 0 || c >= (int)s->columns || r >= (int)s->rows)
        return snake_fail(s);

    // place an empty space char in all map cells
    for (unsigned i = 0; i < s->rows * s->columns; i++)
        s->map[i] = ' ';

    s->head = {c, r};   // head coordinates (x,y)
    s->length = 1;
    s->queue_head = 0;          // init first cell of snake body pointers
    s->snake_body[s->queue_head] = head_ptr(s); // get head cell pointer
    *s->snake_body[s->queue_head] = '@';    // place in head cell the head char

    if (snake_change_direction(s, d) != SNAKE_OKAY)
        return snake_fail(s);

    return (int)(s->status = SNAKE_OKAY);
}

/**
 * Change direction of the snake.
 * @param s snake object pointer
 * @param d direction
 * @return either SNAKE_OKAY or SNAKE_FAIL
 */
int snake_change_direction(snake* s, int d) {
    switch (d) {
        case SNAKE_UP:
        case SNAKE_DOWN:
        case SNAKE_LEFT:
        case SNAKE_RIGHT:
            s->direction = d;
            break;
        default:
            return SNAKE_FAIL;
    }
    return SNAKE_OKAY;
}

unsigned next_queue_head(const snake* const s) {
    return (s->queue_head + 1) % s->max_length;
}

/**
 * Make the snake do a step in the game.
 * @param s snake object pointer
 * @return either SNAKE_FAIL or SNAKE_OKAY
 */
int snake_step(snake* s) {
    // if the snake is not in a valid status, make it fail
    if (s->status != SNAKE_OKAY) {
#if DEBUG
        cout << "1----------------------------" << endl;
#endif
        return SNAKE_FAIL;
    }

    // replace the previous head with '+' if now tail or '#' if body
    char replace_head;
    if (s->length >= 2)
        replace_head = '#';
    else if (s->length == 1)
        replace_head = '+';
    else {
#if DEBUG
        cout << "2----------------------------" << endl;
#endif
        return SNAKE_FAIL;
    }
    *s->snake_body[s->queue_head] = replace_head;

    // change direction of the snake, check if out of bounds
    switch (s->direction) {

        case SNAKE_UP:
#if DEBUG
            cout << "up (" << s->head.first << ", " << s->head.second << "-1)" << endl;
#endif
            if (s->head.second == 0)
                return snake_fail(s);
            s->head.second--;
            break;

        case SNAKE_DOWN:
#if DEBUG
            cout << "down (" << s->head.first << ", " << s->head.second << "+1)" << endl;
#endif
            if (s->head.second + 1 >= s->rows)
                return snake_fail(s);
            s->head.second++;
            break;

        case SNAKE_LEFT:
#if DEBUG
            cout << "left (" << s->head.first << "-1, " << s->head.second << ")" << endl;
#endif
            if (s->head.first == 0)
                return snake_fail(s);
            s->head.first--;
            break;

        case SNAKE_RIGHT:
#if DEBUG
            cout << "right (" << s->head.first << "+1, " << s->head.second << ")" << endl;
#endif
            if (s->head.first + 1 >= s->columns)
                return snake_fail(s);
            s->head.first++;
            break;
    }

    // queue idx, remove character if needed, then check if empty space
    unsigned next_queue_idx = next_queue_head(s);
    if (s->length < s->max_length) s->length++;
    else {
        // free tail old position by putting an empty space
        *s->snake_body[next_queue_idx] = ' ';
        // move the tail to the second last previous position [indirect NICE]
        if (s->length > 1)
            *s->snake_body[(next_queue_idx + 1) % s->max_length] = '+';
    }

#if DEBUG
    cout << "num: " << s->columns * s->head.second + s->head.first << " ";
    cout << "\"" << *head_ptr(s) << "\"" << endl;
#endif
    // if new head position is not an empty space, fail
    if (*head_ptr(s) != ' ') return snake_fail(s);

    s->queue_head = next_queue_idx;
    s->snake_body[next_queue_idx] = head_ptr(s);
    *s->snake_body[next_queue_idx] = '@';
#if DEBUG
    print_map(s);
#endif
    return (int)(s->status = SNAKE_OKAY);
}

/**
 * Give game map string.
 * @param s snake object pointer
 * @return pointer to char of null terminated string
 */
const char* snake_get_field (const snake* s) {
    return s->map;
}

/**
 * Give snake status.
 * @param s snake object pointer
 * @return snake status int
 */
int snake_get_status (const snake* s) {
    return (int)(s->status);
}