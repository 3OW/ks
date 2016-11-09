
#ifndef __INET_HttpDirectServer_H
#define __INET_HttpDirectServer_H

#include <httpServer.h>

using namespace inet;

/**
 * HTTP-Server-Modul mit direkter Kommunikation mit einem HTTP-Client-Modul.
 */
class HttpDirectServer  : public cSimpleModule
{
  protected:
    int numBytes;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};
#endif


