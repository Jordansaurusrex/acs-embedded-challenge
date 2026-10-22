//created by Jordan H, 2026

#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

// Decodes using local packet data, then checks the end marker.
// Returns success or failure; decoded data is not returned to the caller.
bool packet_handler(const char* inputData);

#endif
