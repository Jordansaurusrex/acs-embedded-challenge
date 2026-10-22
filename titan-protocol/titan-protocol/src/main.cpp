//created by Jordan H, 2026

//include file for standard library and project headers
#include <fstream>
#include <iostream>
#include <string>

//project headers
#include "decoder/packet_handler.h"

//standard library declarations
using std::cerr;
using std::cout;
using std::getline;
using std::ifstream;
using std::string;



//--------------------------------------------------------------
// Function definitions
static void read_file(const char* filename)
{
    // open the file for reading
    ifstream file(filename);

    // check if the file was successfully opened
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << '\n';
        return;
    }

    // process the file line by line
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
        // attempt to decode the line into a packet structure
        if (!packet_handler(line.c_str())) {
            cerr << "Could not decode line: " << line << '\n';
            continue;
        }
    }

    // a read error, EOF does not return an error
    if (file.bad()) {
        cerr << "Error reading file: " << filename << '\n';
    }

    // close the file
    file.close();
}

int main(int argc, char* argv[])
{
    //check if more than 2 args if yes error
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [capture-file]\n";
        return 1;
    }

    //if 2nd arg, update filename
    const char* filename = "titan-protocol-capture.txt";
    if (argc == 2) {
        filename = argv[1];
    }

    read_file(filename);
    return 0; 
}