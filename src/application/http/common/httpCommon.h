#ifndef __HTTPCO_H
#define __HTTPCO_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <omnetpp.h>
#include "RawPacket.h"

using namespace std;
using namespace inet;

//---------------------------------------------------------------//

namespace http {

#define HTTP_MAXBUFFER  65535 /**< max. Grösse der Puffer für HTTP-Nachrichten */

// HTTP-Returncodes
#define CODE_200 "200 OK" // OK
#define CODE_400 "400 Bad Request" // Fehlerhafter Request
#define CODE_404 "404 Not Found" // Dokument nicht gefunden
#define CODE_505 "505 HTTP Version not supported" // HTTP-Version nicht unterstützt
#define CODE_403 "403 Forbidden" // Zugriff verboten, wird hier bei Fehlen des "Host"-Feldes verwendet

//---------------------------------------------------------------//

    /**
     * Entfernt fuehrende und folgende Leerzeichen.
     *
     * @return "getrimmte" Zeichenkette
     */
    string trim(string str);

    //---------------------------------------------------------------//

    /**
     * Füllt ein Objekt vom Typ RawPacket mit Nutzdaten.
     *
     * @param packet Omnet++ RawPacket-Objekt
     * @param httpMsg zu versendende HTTP-Message
     */
    void fillPacket(RawPacket *packet, string httpMsg);

    //---------------------------------------------------------------//

};
#endif
