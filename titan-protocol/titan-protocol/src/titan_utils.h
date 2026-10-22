//created by Jordan H, 2026

#ifndef TITAN_UTILS_H
#define TITAN_UTILS_H

// Converts one decimal digit character, returns false for a non digit.
bool process_digit(char byte, int* digit);

// Checks whether (value * 10) + digit fits in an int without changing value.
// digit must be -9 to 9 and have the same sign as value, unless either is zero.
bool can_append_digit(int value, int digit);

#endif
