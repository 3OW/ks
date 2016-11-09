
package ks.simulations.anwendung;

import ks.application.direct.*;

// -----------------------------------------------------

//
// Das Netzwerk
//
network Network
{
    submodules:
        client: HttpDirectClient {

            @display("p=112,116;i=device/pc4");
        }
        server: HttpDirectServer {
            @display("p=418,116;i=device/server2");
        }
    connections:
        client.out --> {  delay = 100ms; } --> server.in;
        server.out --> {  delay = 100ms; } --> client.in;
}
