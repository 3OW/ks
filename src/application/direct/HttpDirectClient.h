#ifndef __INET_HttpDirectClient_H
#define __INET_HttpDirectClient_H

#include <httpClient.h>

/**
 * HTTP-Client-Modul mit direkter Kommunikation mit einem HTTP-Server-Modul.
 */
class HttpDirectClient : public cSimpleModule
{
  protected:

    const char * page; /**< Angefordertes Dokument */
    const char * httpHost; /**< Angefragter Server */
    string httpRequest; /**< HTTP-Request */

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif

