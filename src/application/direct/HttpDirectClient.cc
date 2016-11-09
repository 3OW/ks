#include "HttpDirectClient.h"

Define_Module(HttpDirectClient);

using namespace http;
using namespace inet;

//================================================

void HttpDirectClient::initialize() {
    // Mit Aufruf wird der Versuch begonnen, in dem ein HTTP-Request gesendet wird.
    // Als nächstes wird ein Antwort-Paket vom Server empfangen -> siehe handleMessage

    // Parameter aus ini-Datei lesen und HTTP-Request zusammenstellen
    page = par("page");
    httpHost = par("httpHost");

    // Neues Paket erzeugen
    string req = string("HttpRequest fuer ") + string(page);
    RawPacket *packet = new RawPacket(req.c_str());

    httpRequest = "";

    // HTTP-Nachricht erstellen lasssen
    prepareRequest(httpRequest, packet);

    // Paket an Server senden
    send(packet, "out");
}

//================================================

void HttpDirectClient::handleMessage(cMessage *msg) {
    // Diese Methode wird mit jedem empfangenen Paket (Omnet++-Message) aufgerufen

    string body; /**< Body der HTTP- Nachricht == geliefertes Dokument */
    RawPacket *packet = dynamic_cast<RawPacket *>(msg); /**< Omnet++ Message in Paket-Typ wandeln */
    char *response = new char[HTTP_MAXBUFFER]; /**< Puffer für empfangene HTTP-Nachricht anlegen */

    // HTTP-Nachricht aus Paket nach response kopieren
    packet->getByteArray().copyDataToBuffer(response, HTTP_MAXBUFFER);

    // Ende des Strings markieren
    response[packet->getByteArray().getDataArraySize()] = '\0';

    // Ein empfangenes, einzelnes Fragment zur Auswertung übergeben und den Nutzdatenanteil (HTTP-Body) übernehmen.
    // "body" ist erst >0 wenn das Dokument vollständig empfangen wurde
    body = handleReply(response);

    // Test ob Empfang beendet wurde
    if (body.length() > 0) {
        // Empfang beendet da body-Länge > 0

        // Hier wird in einem Browser das Dokument ausgewertet (angezeigt, abgespielt, abgespeichert, ...)
        // Ausgabe in event log
        EV << "******* Dokument (max. 100 Zeichen): " << body.substr(0, min((int)body.size()-1, 100)) << endl;
        // und auf die Konsole
        cout << "******* Dokument (max. 100 Zeichen): " << body.substr(0, min((int)body.size()-1, 100)) << endl;
    }
    delete msg;
}
