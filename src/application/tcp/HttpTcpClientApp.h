
#ifndef __INET_HTTPCLIENTAPP_H
#define __INET_HTTPCLIENTAPP_H

#include <httpClient.h>
#include <vector>

#include "INETDefs.h"
#include "./TCPSocket.h"
#include "L3AddressResolver.h"


using namespace inet;
using namespace ks;

/**
 * Ein HTTP-Client-Anwendungs-Modul, das über einen kompletten Netzwerkstack mittels TCP  mit einem
 * HTTP-Server-Anwendungs-Modul kommuniziert.
 */
class INET_API HttpTcpClientApp : public cSimpleModule, public ks::TCPSocket::CallbackInterface
{

  protected:
    TCPSocket socket; /**< Eine Variante der "Socket-API" */
    const char *connectAddress; /**< Die IP-Adresse (der Name kann verwendet werden) des Servers. */
    int connectPort; /**< Die Portadresse des Servers. */
    const char *localAddress; /**<  IP-Adresse, die beim Senden verwendet wird; hier: automatisch festgelegt. */
    int localPort; /**< Die eigene Portadresse. */

    const char * page; /**< Angefordertes Dokument */
    const char * httpHost; /**< Angefragter Server */
    string httpRequest; /**< HTTP-Request */

    bool processing = false; /**< Ist wahr, wenn Verarbeitungszeit simuliert wird. */
    bool dataIndicated = false; /**< Ist wahr, wenn TCP einen Datenempfang angekündigt hat. */
    cMessage *dataProcessing = new cMessage("ProcessingData"); /**< Eine "self timer"-Message, bei deren Empfang die simulierte \
        Verarbeitungszeit für Daten endet. */

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    /**
     * Die nachfolgenden Methoden werden nach Auswertung der an TCPSocket::processMessage Message vom Socket gerufen.
     */

    /**
     * Eine Verbindung wurde erfolgreich aufgebaut.
     * @param connId ID der Verbindung
     */
    virtual void socketEstablished(int connId, void *yourPtr) override;
    /**
     * Daten stehen zur Übernahme durch die Anwendung bereit.
     * @param connId ID der Verbindung
     */
    virtual void socketDataIndication(int connId, void *yourPtr) override;
    /**
     * Daten werden an die Anwendung übergeben.
     * @param connId ID der Verbindung
     * @param *msg Zeiger auf die Omnet++-Message (das "Paket")
     */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) override;
};

#endif

