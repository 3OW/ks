//
// Copyright 2004 Andras Varga
//
// This library is free software, you can redistribute it and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#ifndef __INET_HTTPSERVERAPP_H
#define __INET_HTTPSERVERAPP_H


#include <httpServer.h>
#include "INETDefs.h"
#include "./TCPSocket.h"
#include "L3AddressResolver.h"


using namespace inet;
using namespace ks;

/**
 * Ein HTTP-Server-Anwendungs-Modul, das über einen kompletten Netzwerkstack mittels TCP  mit einem
 * HTTP-Client-Anwendungs-Modul kommuniziert.
 */
class INET_API HttpTcpServerApp  : public cSimpleModule, public TCPSocket::CallbackInterface
{
  protected:
    TCPSocket socket; /**< Eine Variante der "Socket-API" */

    const char *localAddress; /**<  IP-Adresse, die beim Senden verwendet wird; hier: automatisch festgelegt. */
    int localPort; /**< Die eigene Portadresse. */
    int numBytes; /**< Länge des Dokuments. */

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    /**
     * Die nachfolgenden Methoden werden nach Auswertung der an TCPSocket::processMessage Message vom Socket gerufen.
     */

    /**
     * Daten werden an die Anwendung übergeben.
     * @param connId ID der Verbindung
     * @param *msg Zeiger auf die Omnet++-Message (das "Paket")
     */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) override;
    /**
     * Die Verbindung wurde vom Partner geschlossen.
     * @param connId ID der Verbindung
     */
    virtual void socketPeerClosed(int connId, void *yourPtr) override;
};

#endif


