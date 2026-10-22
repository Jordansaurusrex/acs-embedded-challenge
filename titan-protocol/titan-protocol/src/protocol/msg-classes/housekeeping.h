//created by Jordan H, 2026

#ifndef HOUSEKEEPING_H
#define HOUSEKEEPING_H

//project headers
#include "../packet_header.h"

struct HousekeepingPayload
{
    int status;       // Zero means operational; other values indicate failure.
    int theta;        // Thousandths of a degree.
    int phi;          // Thousandths of a degree.
    int intensity;    // Unitless.
    int temperature;  // Thousandths of a degree.
};

struct HousekeepingPacket
{
    PacketHeader header;
    HousekeepingPayload payload;
};

// Reads status, theta, phi, intensity, and temperature, advancing offset to the end marker.
// Validates the end marker before returning success.
// inputData must not be null.
// Numeric fields require at least one digit; empty fields and lone minus signs are rejected.
bool process_housekeeping_payload(const char* inputData, size_t& offset,
                                 HousekeepingPayload* payload);

// Prints the decoded header and payload, converting thousandths to degrees.
void print_housekeeping(const HousekeepingPacket& housekeeping);

#endif
