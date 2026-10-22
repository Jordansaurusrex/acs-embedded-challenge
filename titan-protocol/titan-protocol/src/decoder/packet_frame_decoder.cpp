//created by Jordan H, 2026

//include file for standard library and project headers
#include <iostream>

//project headers
#include "packet_frame_decoder.h"
#include "../titan_utils.h"

//standard library declarations
using std::cerr;

//Static constants for packet parsing.
static const char START_MARKER = '$';
static const char END_MARKER = '|';
static const char FIELD_SEPARATOR = ';';
static const int DECIMAL_BASE = 10;


//--------------------------------------------------------------
// Function definitions

bool process_header(const char* inputData, size_t& offset, PacketHeader* header)
{
    if (header == nullptr) {
        cerr << "Invalid packet: null output pointer\n";
        return false;
    }

    // Start of frame '$'
    if (inputData[offset] != START_MARKER) {
        cerr << "Invalid packet: expected start marker $\n";
        return false;
    }
    offset += 1;

    int digit;
    // Command ID
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid command ID: expected a digit\n";
            return false;
        }
        if (!can_append_digit(header->command_id, digit)) {
            cerr << "Invalid command ID: integer overflow\n";
            return false;
        }
        header->command_id = (header->command_id * DECIMAL_BASE) + digit;
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Sequence number
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid sequence number: expected a digit\n";
            return false;
        }
        if (!can_append_digit(header->sequence_number, digit)) {
            cerr << "Invalid sequence number: integer overflow\n";
            return false;
        }
        header->sequence_number = (header->sequence_number * DECIMAL_BASE) + digit;
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Timestamp
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid timestamp: expected a digit\n";
            return false;
        }
        if (!can_append_digit(header->timestamp, digit)) {
            cerr << "Invalid timestamp: integer overflow\n";
            return false;
        }
        header->timestamp = (header->timestamp * DECIMAL_BASE) + digit;
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    return true;
}

bool check_end_marker(const char* inputData, size_t offset)
{
    if (inputData[offset] != END_MARKER) {
        cerr << "Invalid packet: expected end marker |\n";
        return false;
    }
    return true;
}
