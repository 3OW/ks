#include <httpClient.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>


using namespace std;
using namespace inet;

namespace http {

//#############################################################################
// Dieser Bereich ist durch Sie zu analysieren bzw. zu bearbeiten
//#############################################################################

bool headerArrived = false; /**<  Wird true wenn HTTP-Header empfangen wurde. */
long contentLength; /**< Länge des gesamten bodies der HTTP-Nachricht */
map<string, string> header; /**< HTTP-Header als Map: [Header-Feld-Name: Header-Feld-Wert], ... */

string body; /**< der aktuelle HTTP-body */

// Client:
//---------------------------------------------------------------//

void prepareRequest(string httpRequest, RawPacket *packet) {

    // Ausgabe in event log
    EV << "******* Request: " << endl;
    EV << httpRequest << endl;
    // und auf die Konsole
    cout << "******* Request: "  << endl;
    cout << httpRequest << endl;

    // HTTP-Request zum Übertragen vorbereiten
    fillPacket(packet, httpRequest);
}

//---------------------------------------------------------------//

string handleReply(char *resp) {
    // Diese Methode funktioniert nur, wenn die gesammte HTTP-Nachricht auf ein Mal empfangen wurde!
    // Es ist zu beachten, das die HTTP-Nachricht in Fragmenten empfangen werden könnte!
    // Die Fragmentierung erfolgt u.U. in der darunter liegenden Schicht des Netzwerkstacks (Transportschicht)!
    // Zu bemerken ist das erst in den Versuchen zur Transportschicht!

    // C++-String erzeugen, basieren auf dem C-String "resp"
    string response(resp);

    // Meldung in Event-Log schreiben
    EV << "Data arrived: " << "length: " << response.length() << ", data:\n"  << endl;
    EV << response << endl;

    // Meldung auf Konsole schreiben
    cout << "Data arrived: " << "length: " << response.length() << ", data:\n"  << endl;
    cout << response << endl;

    // HTTP-Nachricht auswerten
    parseHttp(response, header, body);

    /* ??? So erhält man z.B. die Länge der HTTP-Nachricht! ??? */
    contentLength = stol(header["Content-Length"]);

    // HTTP-Body zurückliefern
    return body;
}

//---------------------------------------------------------------//

void parseHttp(string message, map<string, string> &headerMap, string &body) {

    // aus der empfangenen HTTP-Nachricht ein C++ Input-String-Stream-Objekt erzeugen
    istringstream resp(message);

    string line;
    string::size_type index;
    string status;

    // erste Zeile des reply's lesen
    getline(resp, line);

    // Status Eintrag erzeugen
    headerMap.insert(make_pair("Status", line));

    // die restlichen HTTP-Header-Einträge auswerten
    while (getline(resp, line) && line != "\r") {
        index = line.find(':', 0); // Doppelpunkt suchen

        // Test ob Ende des HTTP-Reply erreicht
        if (index != string::npos) {
            // noch nicht: also erzeugen eines Eintrags <HTTP-Header-Feldname, HTTP-Header-Feldwert>
            headerMap.insert(
                    make_pair(trim(line.substr(0, index)),
                            trim(line.substr(index + 1))));
        }
    }
    // den Rest der HTTP-Nachricht als HTTP-Nutzdaten (body) kopieren
    body = message.substr(message.find("\r\n\r\n") + 4);
}

//#############################################################################
// ENDE Dieser Bereich ist durch Sie zu analysieren bzw. zu bearbeiten
//#############################################################################

};
