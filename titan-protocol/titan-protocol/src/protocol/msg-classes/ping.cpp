//created by Jordan H, 2026

//include file for standard library and project headers
#include <iostream>

//project headers
#include "ping.h"
#include "../../decoder/packet_frame_decoder.h"

//standard library declarations
using std::cerr;
using std::cout;

//--------------------------------------------------------------
// Function definitions
bool process_ping_payload(const char* inputData, size_t& offset)
{
    if (inputData[offset] != ';') {
        cerr << "Invalid Ping payload: expected an empty field\n";
        return false;
    }
    offset += 1;
    return check_end_marker(inputData, offset);
}

void print_ping(const PingPacket& ping)
{
    cout << "Ping: sequence=" << ping.header.sequence_number
         << ", timestamp=" << ping.header.timestamp << " ms\n";
}
