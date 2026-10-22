//created by Jordan H, 2026

//include file for standard library and project headers
#include <iostream>

//project headers
#include "packet_handler.h"
#include "packet_frame_decoder.h"
#include "../protocol/msg-classes/ping.h"
#include "../protocol/msg-classes/housekeeping.h"

//standard library declarations
using std::cerr;

//--------------------------------------------------------------
// Function definitions

bool packet_handler(const char* inputData)
{
    if (inputData == nullptr) {
        cerr << "Invalid packet: null input pointer\n";
        return false;
    }

    PacketHeader header{};
    size_t offset = 0;
    // Process the packet header first
    if (!process_header(inputData, offset, &header)) {
        return false;
    }

    switch (header.command_id) {
        case COMMAND_PING: {
            PingPacket ping{header};
            if (!process_ping_payload(inputData, offset)) {
                return false;
            }
            print_ping(ping);
            break;
        }
        case COMMAND_HOUSEKEEPING: {
            HousekeepingPacket housekeeping{header, HousekeepingPayload{}};
            if (!process_housekeeping_payload(inputData, offset, &housekeeping.payload)) {
                return false;
            }
            print_housekeeping(housekeeping);
            break;
        }
        default:
            cerr << "Unsupported command ID: " << header.command_id << '\n';
            return false;
    }

    return true;

}
