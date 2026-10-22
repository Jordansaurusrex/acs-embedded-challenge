//created by Jordan H, 2026

#ifndef PING_H
#define PING_H

//project headers
#include "../packet_header.h"

struct PingPacket
{
    PacketHeader header;
};

// Checks the empty Ping payload, advances offset, and validates the end marker.
// inputData must not be null.
bool process_ping_payload(const char* inputData, size_t& offset);

// Prints the decoded Ping header with the timestamp in milliseconds.
void print_ping(const PingPacket& ping);

#endif
