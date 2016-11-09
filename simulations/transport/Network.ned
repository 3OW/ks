
package ks.simulations.transport;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.StandardHost;


network Network
{
    parameters:
        @display("bgb=1080,374");
            
        types:

        channel link extends ned.DatarateChannel
        {
            parameters:
                datarate = default(100Mbps);
        }
        
    submodules:

        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("i=block/cogwheel");
        }

        server: StandardHost {
            parameters:
                @display("p=170,188;i=device/server_l");
            gates:
                pppg[1];
        }

        client: StandardHost {
            parameters:
                @display("p=727,187;i=device/laptop_l");
            gates:
                pppg[1];
        }

        connections:
       client.pppg[0] <--> link <--> server.pppg[0];
}

