#include <httpCommon.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;
using namespace inet;

namespace http {

//---------------------------------------------------------------//
// Unterstützende Funktionen:
//---------------------------------------------------------------//

string trim(string str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//---------------------------------------------------------------//

void fillPacket(RawPacket *packet, string httpMsg) {
    // Datenkonvertierungen
    long sendBytes = httpMsg.length();
    char *ptr = new char[sendBytes];
    httpMsg.copy(ptr, sendBytes);

    // Befüllen des Omnet++ Pakets
    packet->getByteArray().assignBuffer(ptr, sendBytes);
    packet->setByteLength(sendBytes);
}

};
