
package ks.simulations.internet.bignet;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.examples.inet.routerperf.BurstHost;
import inet.node.inet.StandardHost;

network Network
{
    parameters:
        @display("bgb=734,523;bgl=3");

    types:
		// Twisted-Pair-Cable 
        channel tpcable extends ned.DatarateChannel
        {
            delay = 0.5us;
            datarate = 1Gbps;
        }

		// Fiber-Optics-Cable 
        channel focable extends ned.DatarateChannel
        {
            delay = 5us;
            datarate = 10Gbps;
        }

    submodules:

        RProvider: Router {
            @display("p=208,477");
            gates:
                pppg[3];
        }

        hostX: StandardHost {
            @display("p=515,477");
            gates:
                pppg[1];
        }

        hostY: StandardHost {
            @display("p=492,390");
            gates:
                pppg[1];
        }

        RZentral: Router {
            parameters:
                @display("p=39,320;is=n");
            gates:
                pppg[4];
        }

        REtage1: Router {
            parameters:
                @display("p=145,225");
            gates:
                pppg[2];
        }

        REtage2: Router {
            parameters:
                @display("p=39,63");
            gates:
                pppg[3];
        }

        RFirmaA: Router {
            parameters:
                @display("p=382,29");
            gates:
                pppg[2];
        }

        RFirmaB: Router {
            parameters:
                @display("p=382,126");
            gates:
                pppg[2];
        }

        RFirmaC: Router {
            parameters:
                @display("p=382,225");
            gates:
                pppg[3];
        }

        server: StandardHost {
            parameters:
                @display("p=373,320;i=device/server_l");
            gates:
                pppg[1];
        }

        client1: StandardHost {
            parameters:
                @display("i=device/pc;p=671,29");
            gates:
                pppg[1];
        }

        client2: StandardHost {
            parameters:
                @display("i=device/pc;p=671,122");
            gates:
                pppg[1];
        }

        client3: StandardHost {
            parameters:
                @display("i=device/pc;p=671,200");
            gates:
                pppg[1];
        }

        client4: StandardHost {
            parameters:
                @display("i=device/pc;p=671,273");
            gates:
                pppg[1];
        }

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=671,491");
        }

    connections:

        hostX.pppg[0] <--> focable <--> RProvider.pppg[0];
        hostY.pppg[0] <--> focable <--> RProvider.pppg[1];

        RZentral.pppg[0] <--> focable <--> RProvider.pppg[2];

        RZentral.pppg[1] <--> focable <--> REtage2.pppg[0];
        RZentral.pppg[2] <--> focable <--> REtage1.pppg[0];

        REtage1.pppg[1] <--> focable <--> RFirmaC.pppg[0];
        REtage2.pppg[1] <--> focable <--> RFirmaA.pppg[0];
        REtage2.pppg[2] <--> focable <--> RFirmaB.pppg[0];

        RZentral.pppg[3] <--> tpcable <--> server.pppg[0];

        RFirmaA.pppg[1] <--> tpcable <--> client1.pppg[0];
        RFirmaB.pppg[1] <--> tpcable <--> client2.pppg[0];

        RFirmaC.pppg[1] <--> tpcable <--> client3.pppg[0];
        RFirmaC.pppg[2] <--> tpcable <--> client4.pppg[0];
}
