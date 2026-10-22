//created by Jordan H, 2026

#ifndef PACKET_HEADER_H
#define PACKET_HEADER_H

//include file for standard library and project headers
#include <stddef.h>

//packet data definitions
enum CommandId
{
    COMMAND_PING = 1,
    COMMAND_HOUSEKEEPING = 10  // Matches the capture data.
};

// Chose a plain struct to keep decoded data simple and shared through composition.
// Considered an OO packet hierarchy, but inheritance and virtual methods are
// unnecessary for the two message types and their current parsing needs.
// Use int for all fields to share one overflow check and keep parsing simple.
// Sequence and timestamp accept 0 to INT_MAX; larger values are rejected.
// With a 32bit int, the millisecond timestamp supports about 24.9 days.
struct PacketHeader
{
    int command_id;
    int sequence_number;
    int timestamp;  // Milliseconds elapsed.
};

#endif
