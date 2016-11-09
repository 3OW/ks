
#include "HttpDirectServer.h"

Define_Module(HttpDirectServer);

using namespace http;

//===========================================

void HttpDirectServer::initialize() {
    // Länge des HTML-Dokuments aus Ini-Datei lesen
    numBytes = par("numBytes");
}

//===========================================

void HttpDirectServer::handleMessage(cMessage *msg) {
    // Diese Methode wird einmal beim Empfang des HTTP-Requests (Omnet++-Message) aufgerufen

    // Neue, leere  HTTP-Nachricht erzeugen
    RawPacket *httpPacket = new RawPacket("HttpReply"); // "HttpReply" erscheint in Event-Logs als der Name des Omnet++-Events

    RawPacket *packet = dynamic_cast<RawPacket *>(msg); /**< Omnet++ Message in Paket-Typ wandeln */
    char *request = new char[HTTP_MAXBUFFER]; /**< Puffer für empfangene HTTP-Nachricht anlegen */

    // Eintrag in event log
    EV << "receiving data\n";

    // HTTP-Nachricht aus Paket nach request kopieren
    packet->getByteArray().copyDataToBuffer(request, HTTP_MAXBUFFER);

    // Antwort erzeugen lassen
    prepareReply(request, httpPacket, numBytes);

    // Eintrag in event log
    EV << "sending data\n";

    // Senden des Pakets
    // Senden eines Pakets als Omnet++-Message (Objekte müssen als Duplikate übergeben werden)
    send((cMessage *) httpPacket->dup(), "out");

    delete msg;
}
