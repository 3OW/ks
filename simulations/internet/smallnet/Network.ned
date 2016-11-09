
package ks.simulations.internet.smallnet;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.examples.inet.routerperf.BurstHost;


network Network
{
    @display("bgb=789,273");
    types:
        channel cable extends ned.DatarateChannel
        {
            delay = 1us;
            datarate = 100Mbps;
        }

    submodules:

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=64,28;is=vs");
                assignAddresses = true;
                assignDisjunctSubnetAddresses = false;
                addDefaultRoutes = false;
                addStaticRoutes = false;
                addSubnetRoutes = false;
                optimizeRoutes = false;
        }

        router1: Router {
            parameters:
                @display("p=290,70");

            gates:
                pppg[2];
        }

        router2: Router {
            parameters:
                @display("p=526,70");

            gates:
                pppg[2];
        }

        client: BurstHost {
            parameters:
                @display("i=device/laptop;p=31,194");

            gates:
                pppg[1];
        }

        server: BurstHost {
            parameters:
                @display("p=714,194;i=device/server_l");

            gates:
                pppg[1];
        }
    connections:
        router1.pppg[1] <--> cable <--> client.pppg[0];
        router2.pppg[1] <--> cable <--> server.pppg[0];
        router1.pppg[0] <--> cable <--> router2.pppg[0];
}
