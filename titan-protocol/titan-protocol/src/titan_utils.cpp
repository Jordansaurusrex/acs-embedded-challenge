//created by Jordan H, 2026

//include file for standard library and project headers
#include <climits>

//project headers
#include "titan_utils.h"

static const int DECIMAL_BASE = 10;

//--------------------------------------------------------------
// Function definitions

bool process_digit(char byte, int* digit)
{
    *digit = byte - '0';
    return ((*digit >= 0) && (*digit <= 9));
}

bool can_append_digit(int value, int digit)
{
    // Appending calculates (value * 10) + digit. Check it fits before calculating.
    if ((value >= 0) && (digit >= 0)) {
        // INT_MAX - digit is the space left for value * 10 after allowing for the digit.
        // Divide that space by 10 so we can compare value without multiplying it.
        return (value <= ((INT_MAX - digit) / DECIMAL_BASE));
    }

    // For a negative value, INT_MIN - digit is the lower limit left for value * 10.
    // Divide by 10 and check value stays above it. The signed digit may also be zero.
    return (value >= ((INT_MIN - digit) / DECIMAL_BASE));
}
