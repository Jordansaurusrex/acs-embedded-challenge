//created by Jordan H, 2026

//include file for standard library and project headers
#include <iostream>
#include <iomanip>
#include <sstream>

//project headers
#include "housekeeping.h"
#include "../../titan_utils.h"
#include "../../decoder/packet_frame_decoder.h"

//standard library declarations
using std::cerr;
using std::cout;
using std::fixed;
using std::ostringstream;
using std::setprecision;

static const double UNITS_PER_DEGREE = 1000.0;
static const char FIELD_SEPARATOR = ';';
static const int DECIMAL_BASE = 10;

//--------------------------------------------------------------
// Function definitions
bool process_housekeeping_payload(const char* inputData, size_t& offset,
                                 HousekeepingPayload* payload)
{
    if (payload == nullptr) {
        cerr << "Invalid housekeeping payload: null output pointer\n";
        return false;
    }

    int digit;
    // Status
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid housekeeping status: expected a digit\n";
            return false;
        }
        if (!can_append_digit(payload->status, digit)) {
            cerr << "Invalid housekeeping status: integer overflow\n";
            return false;
        }
        payload->status = (payload->status * DECIMAL_BASE) + digit;
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Theta
    int sign = 1;
    if (inputData[offset] == '-') {
        sign = -1;
        offset += 1;
    }
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid housekeeping theta: expected a digit\n";
            return false;
        }
        if (!can_append_digit(payload->theta, sign * digit)) {
            cerr << "Invalid housekeeping theta: integer overflow\n";
            return false;
        }
        payload->theta = (payload->theta * DECIMAL_BASE) + (sign * digit);
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Phi
    sign = 1;
    if (inputData[offset] == '-') {
        sign = -1;
        offset += 1;
    }
    
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid housekeeping phi: expected a digit\n";
            return false;
        }
        if (!can_append_digit(payload->phi, sign * digit)) {
            cerr << "Invalid housekeeping phi: integer overflow\n";
            return false;
        }
        payload->phi = (payload->phi * DECIMAL_BASE) + (sign * digit);
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Intensity
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid housekeeping intensity: expected a digit\n";
            return false;
        }
        if (!can_append_digit(payload->intensity, digit)) {
            cerr << "Invalid housekeeping intensity: integer overflow\n";
            return false;
        }
        payload->intensity = (payload->intensity * DECIMAL_BASE) + digit;
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    // Temperature
    sign = 1;
    if (inputData[offset] == '-') {
        sign = -1;
        offset += 1;
    }
    do {
        if (!process_digit(inputData[offset], &digit)) {
            cerr << "Invalid housekeeping temperature: expected a digit\n";
            return false;
        }
        if (!can_append_digit(payload->temperature, sign * digit)) {
            cerr << "Invalid housekeeping temperature: integer overflow\n";
            return false;
        }
        payload->temperature = (payload->temperature * DECIMAL_BASE) + (sign * digit);
        offset += 1;
    } while (inputData[offset] != FIELD_SEPARATOR);
    offset += 1;

    return check_end_marker(inputData, offset);
}

void print_housekeeping(const HousekeepingPacket& housekeeping)
{
    ostringstream output;
    output << fixed << setprecision(3)
           << "Housekeeping: sequence=" << housekeeping.header.sequence_number
           << ", timestamp=" << housekeeping.header.timestamp << " ms"
           << ", status=" << housekeeping.payload.status
           << (housekeeping.payload.status == 0 ? " (operational)" : " (failure)")
           << ", theta=" << housekeeping.payload.theta / UNITS_PER_DEGREE << " deg"
           << ", phi=" << housekeeping.payload.phi / UNITS_PER_DEGREE << " deg"
           << ", intensity=" << housekeeping.payload.intensity
           << ", temperature=" << housekeeping.payload.temperature / UNITS_PER_DEGREE
           << " deg\n";
    cout << output.str();
}
