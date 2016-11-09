#ifndef __HTTPC_H
#define __HTTPC_H

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

    /**
     * Parsen eines Http-Reply, sortiert die Felder in m ein, den Rest in body.
     * Erzeugt spezielles Feld "Status".
     *
     * @param message empfangene HTTP-Nachricht
     * @param m Map mit key: Name des HTTP Header-Feldes und value: Wert des ...
     * @param body Body der HTTP-Nachricht
     */
    void parseHttp(string message, map<string, string> &m, string &body);

    //---------------------------------------------------------------//

    /**
     * Befüllt ein RawPacket-Objekt mit einer HTTP-Nachricht
     *
     * @param httpRequest HTTP-Request
     * @param packet Zeiger auf das zu füllende Paket
     */
    void prepareRequest(string httpRequest, RawPacket *packet);

//---------------------------------------------------------------//

    /**
     * Liefert leeren String bei unvollständiger HTTP-Nachricht, oder Nachricht.
     * Wird bei jedem Datenempfang gerufen, bis die in "Content-Length" angegebene Datenmenge empfangen wurde.
     *
     * @param response empfangene Antwort
     * @return HTTP-Nachricht bei komplettem Empfang aller Fragmente oder leere Zeichenkette
     */
    string  handleReply(char *response);

};
#endif
