#ifndef __HTTPS_H
#define __HTTPS_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <omnetpp.h>
#include "RawPacket.h"
#include <httpCommon.h>

using namespace std;
using namespace inet;

//---------------------------------------------------------------//

namespace http {

//---------------------------------------------------------------//

#define SERVER_NAME "lab.ks.de" // Der eigene Name

//---------------------------------------------------------------//

    /**
     * Parsen eines GET-Request.
     * Liefert den Pfad des zu liefernden Dokuments ohne fuehrendes "/".
     * oder HTTP-Fehlercodes
     *
     * @param message die empfangene HTTP-Nachricht
     * @return Pfad des zu liefernden HTTP-Objekts, bei Fehler werden Fehler ais Zeichenkette geliefert
     */
    string parseGET(string message);

//---------------------------------------------------------------//

    /**
     * Liefert eine  HTTP-Nachricht in packet.
     *
     * @param request: angefordertes Dokument
     * @param packet: Zeiger auf zu füllendes Paketen
     * @param numBytes: Länge des zu liefernden Dokuments oder 0
     */
    void prepareReply(char *request, RawPacket *packet, int numBytes = 0);

};
#endif
