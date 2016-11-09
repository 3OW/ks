
#include "./HttpTcpClientApp.h"

#include "L3AddressResolver.h"

using namespace http;

Define_Module(HttpTcpClientApp);

//================================================

void HttpTcpClientApp::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {

        // Parameter laden
        localPort = par("localPort");
        connectAddress = par("connectAddress");
        localAddress = par("localAddress");
        connectPort = par("connectPort");

        // Parameter aus ini-Datei lesen und HTTP-Request zusammenstellen
        page = par("page");
        httpHost = par("httpHost");

        httpRequest = "";

    } else if (stage == INITSTAGE_APPLICATION_LAYER) {

        // Socket einrichten
        socket.readDataTransferModePar(*this);
        socket.bind(
                *localAddress ?
                        L3AddressResolver().resolve(localAddress) : L3Address(),
                localPort);
        socket.setCallbackObject(this);
        socket.setOutputGate(gate("tcpOut"));

        // connect
        EV << "issuing OPEN command\n";

        L3Address destination;
        L3AddressResolver().tryResolve(connectAddress, destination);

        if (destination.isUnspecified())
            EV << "cannot resolve destination address: " << connectAddress
                      << endl;
        else {
            socket.connect(destination, connectPort);
        }
    }
}

//================================================

void HttpTcpClientApp::handleMessage(cMessage *msg) {
    // Test auf Art der Message
    if (msg == dataProcessing) {
        // Simulation der Verarbeitungszeit ist beendet
        if (processing) {
            processing = false;
            if (dataIndicated) {
                dataIndicated = false;
                socket.receive();
            }
        }
    } else {
        // Daten sind empfangen worden
        // Der Socket entscheidet über den Aufruf von "socketX"-Methode
        socket.processMessage(msg);
    }
}

//================================================

void HttpTcpClientApp::socketDataIndication(int connId, void *ptr) {
    EV << "TCP möchte Daten an Anwendung übergeben\n";

    // Daten sind liegen bereit
    dataIndicated = true;

    // Test ob Anwendungg noch "Daten verarbeitet"
    if (!processing) {
        // Nein, also Datenempfang einleiten, Daten werden nun per Message übergeben
        socket.receive();
    }
}

//================================================

void HttpTcpClientApp::socketDataArrived(int connId, void *ptr, cPacket *msg,
        bool urgent) {

    string body;
    RawPacket *respArray = dynamic_cast<RawPacket *>(msg);
    char *resp = new char[HTTP_MAXBUFFER];

    // Nutzdaten extrahieren nach resp
    respArray->getByteArray().copyDataToBuffer(resp, HTTP_MAXBUFFER);

    // Ende des Strings markieren
    resp[respArray->getByteArray().getDataArraySize()] = '\0';

    std::string response(resp);
    delete msg;

    body = handleReply(resp);

    if (body.length() > 0) {
        // Empfang beendet
        EV << "HTTP-Body: Länge: " << body.length() << "\nHTTP:Body (max. 100 Zeichen);\n" << body.substr(0, min((int)body.size()-1, 100)) << endl;
        cout << "HTTP-Body: Länge: " << body.length() << "\nHTTP:Body (max. 100 Zeichen);\n" << body.substr(0, min((int)body.size()-1, 100)) << endl;
        socket.close();
    } else {
        // weiter empfangen
        if (processing) {
            // Verarbeitungszeit der Anwendung verlängern, dazu laufenden Timeout beenden
            cancelEvent(dataProcessing);
        } else {
            // Beginn der Simulation der Verabeitungszeit
            processing = true;
        }
        // Simulation der Bearbeitungsdauer initiieren
        scheduleAt(simTime() + par("processingTime"), dataProcessing);
    }
}

//================================================

void HttpTcpClientApp::socketEstablished(int connId, void *ptr) {
    EV << "Verbindung aufgebaut, jetzt Daten senden.\n";

    RawPacket *msg = new RawPacket("HttpRequest");

    // HTTP-Request erstellen lasssen
    prepareRequest(httpRequest, msg);

    // Paket an Server senden
    socket.send(msg);
}
