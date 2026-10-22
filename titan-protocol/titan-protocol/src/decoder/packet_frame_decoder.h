//created by Jordan H, 2026

#ifndef PACKET_FRAME_DECODER_H
#define PACKET_FRAME_DECODER_H

//project headers
#include "../protocol/packet_header.h"

// Reads command ID, sequence number, and timestamp into the header.
// Advances offset to the payload, returns false on error.
// inputData must not be null.
// Numeric fields require at least one digit; empty fields are rejected.
bool process_header(const char* inputData, size_t& offset, PacketHeader* header);

// Checks the end marker at offset. inputData must not be null.
// By design, assumes one message per line; content after the end marker is ignored.
// A future improvement could parse multiple messages on the same line.
bool check_end_marker(const char* inputData, size_t offset);

#endif
