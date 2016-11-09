
#include "HttpTcpServerApp.h"

Define_Module(HttpTcpServerApp);

using namespace http;

//===========================================

void HttpTcpServerApp::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {

        // Länge des HTML-Dokuments aus Ini-Datei lesen
        numBytes = par("numBytes");

        localPort = par("localPort");
        localAddress = "";

    } else if (stage == INITSTAGE_APPLICATION_LAYER) {

        socket.readDataTransferModePar(*this);
        socket.setCallbackObject(this);
        socket.setOutputGate(gate("tcpOut"));
        socket.bind(*localAddress ? L3Address(localAddress) : L3Address(),
                localPort);
        socket.listenOnce();
    }
}

//===========================================

void HttpTcpServerApp::handleMessage(cMessage *msg) {
    socket.processMessage(msg);
}

//===========================================

void HttpTcpServerApp::socketDataArrived(int connId, void *yourPtr,
        cPacket *msg, bool urgent) {

    // Neue, leere  HTTP-Nachricht erzeugen
    RawPacket *httpPacket = new RawPacket("HttpReply"); // "HttpReply" erscheint in Event-Logs als der Name des Omnet++-Events

    RawPacket *reqArray = dynamic_cast<RawPacket *>(msg);
    char *req = new char[HTTP_MAXBUFFER];

    // Nutzdaten extrahieren nach req
    reqArray->getByteArray().copyDataToBuffer(req, HTTP_MAXBUFFER);
    std::string response(req);
    delete msg;

    //  HTTP-Reply erzeugen
    prepareReply(req, httpPacket, numBytes);

    EV << "sending data\n";

    socket.send((cMessage *) httpPacket->dup());
}

//===========================================

void HttpTcpServerApp::socketPeerClosed(int connId, void *yourPtr) {
    // close the connection (if not already closed)
    if (socket.getState() == TCPSocket::PEER_CLOSED) {
        EV << "remote TCP closed, closing here as well\n";
        socket.close();
    }
}
