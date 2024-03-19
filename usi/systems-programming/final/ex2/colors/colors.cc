#include <iostream>
#include <string>

#include "colors.h"

#define HEX_MULT 16

using std::toupper;
using std::string;
using std::cout;
using std::endl;

int char_hex_to_int (char c) {
    c = toupper(c);

    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default: return -1;
    }
}

/**
 * assigns color object from a string  (0, 6) hex chars repr 3 bytes (each 4 bits)
 * @param c
 * @param s
 */
void string_to_color(color *c, const char *s) {
    string string_color(s);

    c->red = 0;
    c->green = 0;
    c->blue = 0;

    if (string_color.empty()) return;

    bool color_put[6];

    for (bool & i : color_put) i = false;

    for (int i = 0; i < int(string_color.size()); i++) {

        int num = char_hex_to_int(string_color[i]);
        if (num == -1) {
            break;
        } else {
            if (i <= 1) {
                // red
                if (i % 2 == 0) {
                    c->red = HEX_MULT * num;
                } else {
                    c->red += num;
                }
            } else if (i <= 3) {
                // green
                if (i % 2 == 0) {
                    c->green = HEX_MULT * num;
                } else {
                    c->green += num;
                }
            } else if (i <= 5) {
                if (i % 2 == 0) {
                    c->blue = HEX_MULT * num;
                } else {
                    c->blue += num;
                }
            }
        }
    }
}